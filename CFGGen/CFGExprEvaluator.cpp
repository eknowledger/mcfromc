
#include "CFGExprEvaluator.h"
#include "SyntaxUtils.h"
#include "SNode.h"
#include "SIdentifierNode.h"
#include "Block.h"
#include "boost\graph\depth_first_search.hpp"
#include "SAssignmentNode.h"
#include "MCGraph.h"
#include "boost/make_shared.hpp"
#include <set>
#include <vector>

namespace{
	typedef std::set<FP_CFG_ID> FPWorkSet;
	class ExprEvalVisitor: public boost::default_dfs_visitor 
	{
		friend class CFGExprEvaluator;
	public:
		ExprEvalVisitor(FPWorkSet& fp_ws,
						FPIDToVarState& fpStates,
						bool& firstTime,
						bool& conclusionChanged)
			: m_fpWorkset(fp_ws)
			, m_varStateAtFP(fpStates)
			, m_firstRun(firstTime)
			, m_conclusionChanged(conclusionChanged)
		{
		}

		template<typename Vertex,typename Graph>
		void start_vertex(Vertex s,const Graph& g)
		{
			const CFG* cfg = dynamic_cast<const CFG *>(&g);
			ASSERT_RETURN_VOID(cfg != NULL);
			m_conclusionChanged = false;
			//creates a new empty mc.
			m_emptyMC = boost::make_shared<MCGraph>();
			m_emptyMC->addVariables(cfg->Variables());
			m_emptyMC->addConstants(cfg->Constants());
			if(m_firstRun){
				initVarStates(m_varStateAtFP[s],cfg->Variables(),cfg->Constants());
			}
		}

		template <typename Edge, typename Graph>
		void examine_edge(Edge e, const Graph& g)
		{
			//copy value map from source-out to target-in.
			FP_CFG_ID s = boost::source(e,g);
			FP_CFG_ID t = boost::target(e,g);
			
			FPointWeakPtr wpSrcFP = boost::get(boost::vertex_attachedFP,g,s);
			FPointWeakPtr wpTgtFP = boost::get(boost::vertex_attachedFP,g,t);
			FPSharedPtr srcFP = wpSrcFP.lock();
			FPSharedPtr tgtFP = wpTgtFP.lock();
			ASSERT_RETURN_VOID(srcFP != NULL && tgtFP != NULL);

			//we init the state if the state of source FP.
			VarToValue state = m_varStateAtFP[srcFP->cfgID()];
			MCSharedPtr newMC = boost::make_shared<MCGraph>();
			*newMC = *m_emptyMC;
			newMC->setFlowPoints(srcFP,tgtFP);
			//currently we only generate try to evaluate on f->g where f is expression block since this is 
			//the only relevant transition for MCs
			if(srcFP->Type() == FlowPoint::EXPRESSION_BLOCK){
				//checks if we need to process the current expression flowpoint if not lets move on
				FPWorkSet::iterator srcItr = m_fpWorkset.find(s);
				/*if(srcItr != m_fpWorkset.end()){*/
					const std::vector<FlowPoint*>& exprsFPs = (static_cast<Block*>(srcFP.get()))->flowPoints(); 
					for (size_t i = 0; i < exprsFPs.size(); ++i)
						evaluateExprFlowPoint(exprsFPs[i],state);
				//}
			}
			else{
				//update the new MC with its invariants.

				bool isCondHoldEdge = boost::get(boost::edge_invariantTrue,g,e);
				evaluateBranchInvariants(srcFP, newMC, isCondHoldEdge);
			}
			//compute the MC's size change for this edge.
			TransitionVariantSet changes = ComputeExprBlockVariants(m_varStateAtFP[s],state);
			for(TransitionVariantSet::iterator transItr = changes.begin(); transItr != changes.end(); ++transItr)
				newMC->addTrnasitionVariant(*transItr);

			//gets our current MC, checks if this has changed update it
			//and mark it as changed.
			MCWeakPtr mcWeak = boost::get(boost::edge_sizeChange,g,e);
			MCSharedPtr attachedMC = mcWeak.lock();
			ASSERT_RETURN_VOID(attachedMC != NULL);
			if(*newMC != *attachedMC){
				//our transition variant conclusion has changed
				*attachedMC = *newMC;
				m_conclusionChanged = true;
			}
			
			mergeStateInFPVar(tgtFP,state);
			//remove ourself from the workset.
			FPWorkSet::iterator srcItr = m_fpWorkset.find(s);
			if(srcItr != m_fpWorkset.end())
				m_fpWorkset.erase(srcItr);

			////we haven't change our state variables values meaning we should not notify
			////out out edges.
			//if(!changed)
			//	return;

			//adds all the out flowpoints from the source flowpoint to the workset.
			Graph::out_edge_iterator out_i,out_end;
			for(boost::tie(out_i,out_end) = boost::out_edges(t,g); out_i != out_end; ++out_i){
				if(boost::out_degree(boost::target(*out_i,g),g) > 0)
					m_fpWorkset.insert(boost::target(*out_i,g));
			}
		}

		template <typename Edge, typename Graph>
		void forward_or_cross_edge(Edge e, const Graph& g)
		{

		}

		template <typename Edge, typename Graph>
		void back_edge(Edge e, const Graph& g)
		{

		}

		inline FPIDToVarState getFlowPointsStates()
		{
			return m_varStateAtFP;
		}

	private:
		//should use SMART ptr !!!!
		void evaluateExprFlowPoint(FlowPoint* exprFP, VarToValue& state) const
		{
			SNode* expr = exprFP->syntaxNode();
			ASSERT_RETURN_VOID(expr != NULL && expr->children().size() > 0);

			ParamName var;
			SPExpr val;
			SNode* identNode = expr->children()[0];
			ASSERT_RETURN_VOID(identNode != NULL && identNode->Type() == ID);
			//this is and variable node gets its name.
			var = static_cast<SIdentifierNode*>(expr->children()[0])->name();
			switch(expr->Type())
			{
			case ASSIGNMENT_EXPR:
				val = evaluateAssignmentExpr(expr);
				break;
			case POST_INCREMENT_EXPR:
			case PRE_INCREMENT_UNARY_EXPR:
				val = ExprMgr::the().createVar(var, 1);
				break;
			case POST_DECREMENT_EXPR:
			case PRE_DECREMENT_UNARY_EXPR:
				val = ExprMgr::the().createVar(var, -1);
				break;
			default:
				val = ExprMgr::the().createUndefined();
				break;
			}
			ASSERT_RETURN_VOID(val != NULL);
			state[var] = val->Evaluate(state);
		}

		SPExpr evaluateAssignmentExpr(SNode* expr) const
		{
			SPExpr val;
			SPExpr varEx = ExprMgr::the().create(expr->children()[0]);
			if (expr->children().size() > 2)
				val = ExprMgr::the().create(expr->children()[2]);
			else
				val = ExprMgr::the().create(expr->children()[1]);

			SAssignmentNode* assignment = (SAssignmentNode*)expr;
			if (assignment->subType() == ADD_ASSIGNMENT_EXPR) {
				val = (*varEx + *val);
			}
			else if (assignment->subType() == SUB_ASSIGNMENT_EXPR) {
				val = (*varEx - *val);
			}
			else if (assignment->subType() == MUL_ASSIGNMENT_EXPR) {
				val = (*varEx * *val);
			}
			else if (assignment->subType() == DIV_ASSIGNMENT_EXPR) {
				val = (*varEx / *val);
			}
			else if (assignment->subType() == MOD_ASSIGNMENT_EXPR) {
				val = (*varEx % *val);
			}

			return val;
		}

		void evaluateBranchInvariants(FPSharedPtr fp,MCSharedPtr newMC, bool isCondHoldEdge) const
		{
			ASSERT_RETURN_VOID(fp != NULL);
			ASSERT_RETURN_VOID(newMC != NULL);

			SNode* node = fp->syntaxNode();
			ASSERT_RETURN_VOID(node != NULL);
		
			SNode* condition = NULL;
			switch(node->Type())
			{
			case WHILE_LOOP:
			case CONDITION_IF:
			case CONDITION_IF_ELSE:
				condition = node->children()[0];
				break;
			case DO_WHILE_LOOP:
			case FOR_LOOP:
				condition = node->children()[1];
				break;
			default:
				ASSERT_RETURN_VOID(!"Un Handled Branch Node");
			}

			ASSERT_RETURN_VOID(condition != NULL);
			std::vector<SNode*> subConditions;
			findRelevantSubConditions(condition, subConditions);
			//currently on the edge where the condition does not hold, we only handle
			//a case where there is only one expression since !cond may be complex and result
			// && to become || and this we do not handle
			if(!isCondHoldEdge){
				if(subConditions.size() != 1)
					return;
				
				SPExpr orderCond = ExprMgr::the().create(subConditions[0]);
				ASSERT_RETURN_VOID(orderCond != NULL);
				InvariantMember inv = computeExprInvariant((const BinExpr&)*orderCond);
				Invariant notInv = InvariantNotOp(inv);
				for(Invariant::iterator invItr = notInv.begin(); invItr != notInv.end(); ++invItr)
				{
					newMC->addEdgeFromInvariant(fp,*invItr);
				}
				return;
			}

			for (size_t i = 0; i < subConditions.size(); ++i)
			{
				SPExpr orderCond = ExprMgr::the().create(subConditions[i]);
				ASSERT_LOOP_CONTINUE(orderCond != NULL);
				InvariantMember inv = computeExprInvariant((const BinExpr&)*orderCond);
				newMC->addEdgeFromInvariant(fp,inv);
			}
		}

		void findRelevantSubConditions(SNode* node,std::vector<SNode*>& subConditions) const
		{
			if (node->IsOrderCondition())
			{
				subConditions.push_back(node);
			}
			else if (node->Type() == LOGICAL_AND_EXPR)
			{
				findRelevantSubConditions(node->children()[0], subConditions);
				findRelevantSubConditions(node->children()[1], subConditions);
			}
		}

		InvariantMember computeExprInvariant(const BinExpr& expr) const
		{
			if (expr.IsCondition())
			{
				SPExpr left = expr.Left();
				SPExpr right = expr.Right();
				std::string wsLeft, wsRight;
				if (left->IsVariable())
				{
					wsLeft = ((AtomExpr*)left.get())->Name();
				}
				else if (left->HasValue())
				{
					std::ostringstream ostr;
					ostr << ((AtomExpr*)left.get())->Value();
					wsLeft = ostr.str();
				}
				if (right->IsVariable())
				{
					wsRight = ((AtomExpr*)right.get())->Name();
				}
				else if (right->HasValue())
				{
					std::ostringstream ostr;
					ostr << ((AtomExpr*)right.get())->Value();
					wsRight = ostr.str();
				}

				if (wsLeft.size() > 0 && wsRight.size() > 0)
				{
					return InvariantMember(wsLeft, order(expr.OpType()), wsRight);	
				}
			}

			return InvariantMember("", END_ORDER,"");
		}

		Order order(OperatorType opType) const
		{
			Order o = END_ORDER;
			switch (opType)
			{
			case OP_LESS:
				o = LESS;
				break;
			case OP_LEQ:
				o = LEQ;
				break;
			case OP_EQ:
				o = EQ;
				break;
			case OP_GEQ:
				o = GEQ;
				break;
			case OP_GREATER:
				o = GREATER;
				break;
			}

			return o;
		}

		bool mergeStateInFPVar(FPSharedPtr spFP,const VarToValue& transitionState)
		{
			VarToValue& fpSavedState = m_varStateAtFP[spFP->cfgID()];
			//if the target's flowpoint's state is empty it means we do not know anything
			//then just get the current given state.
			if(fpSavedState.empty()){
				fpSavedState = transitionState;
				return true;
			}
			
			bool changed = false;
			for(VarToValue::const_iterator varItr = transitionState.begin(); varItr != transitionState.end(); ++varItr){
				VarToValue::iterator varAtFPItr = fpSavedState.find(varItr->first);
				if(varAtFPItr != fpSavedState.end())
				{
					//check if the value is in equal.
					Order o = ExprMgr::the().ComputeOrder(varAtFPItr->second,varItr->second,fpSavedState);
					if(o != EQ){
						//the variable value does not agree with the given state , we do not
						//know what is the correct value than we remove it to get a new unkown value on next use.
						varAtFPItr->second = ExprMgr::the().createUndefined();
						changed = true;
					}
				}
			}

			return changed;
		}

		void initVarStates(VarToValue& state,const ParamNameSet& knownVars,const VarToValue& constants){
			for(ParamNameSet::const_iterator varItr = knownVars.begin(); varItr != knownVars.end(); ++varItr){
				state[*varItr] = ExprMgr::the().createUndefined();
			}
			state.insert(constants.begin(),constants.end());
		}

		TransitionVariantSet ComputeExprBlockVariants(VarToValue& inValue, VarToValue& outValue) const
		{
			TransitionVariantSet transitionVariantSet;
			//for all variable values at block end
			for (VarToValueIt outIt = outValue.begin(); outIt != outValue.end(); ++outIt)
			{
				//and for all variable values at block begin
				for (VarToValueIt inIt = inValue.begin(); inIt != inValue.end(); ++inIt)
				{
					ParamName var1 =(*inIt).first;
					ParamName var2 =(*outIt).first;
					//find order between 2 variable values
					Order o = ExprMgr::the().ComputeOrder(outValue[var2], inValue[var1], outValue);
					if (o != END_ORDER)
					{
						//order found, add invariant
						transitionVariantSet.insert(boost::make_tuple(var1, o, var2));
					}
				}
			}

			return transitionVariantSet;
		}




		//should be replaced by exterior property map.
		FPIDToVarState& m_varStateAtFP;

		FPWorkSet& m_fpWorkset;
	private:
		bool &m_firstRun;
		bool &m_conclusionChanged;
		MCSharedPtr m_emptyMC;
	};
}

void CFGExprEvaluator::Evaluate()
{
	//adds all the program state variables to the MCs
	m_cfg.UpdateTransitionsWithVars();

	//adds all the flowpoints into the workset.
	CFG::vertex_iterator fpItr,fpItrEnd;
	FPWorkSet unprocessedFPs;
	for(boost::tie(fpItr,fpItrEnd) = boost::vertices(m_cfg); fpItr != fpItrEnd; ++fpItr){
		if(boost::out_degree(*fpItr,m_cfg) > 0)
			unprocessedFPs.insert(*fpItr);
	}

	bool firstTime = true;
	bool concChanged =false;

	FPIDToVarState fpStatesResult;
	ExprEvalVisitor vis(unprocessedFPs,fpStatesResult,firstTime,concChanged);

	do{
		//process the C.F.G in DFS and try to evaluate expressions.
		if (m_cfg.Start())
		{
			FP_CFG_ID s = m_cfg.Start()->cfgID();
			boost::depth_first_search(m_cfg, vis, boost::get(boost::vertex_color,m_cfg),s);
		}
		else
		{
			//no starting point set - do regular dfs
		}
		vis.m_firstRun = false;
	}
	////this is an iterative algorithm until we reached l.f.p (where there is no more unprocessed flowpoint)
	while(vis.m_conclusionChanged);

	//generate the MCs, something like
	//updateMCsWithTransitionsVariants(fpStatesResult);

}

void CFGExprEvaluator::updateMCsWithTransitionsVariants(FPIDToVarState& fpStates)
{
	CFG::edge_iterator e_i,e_end;
	for(boost::tie(e_i,e_end) = boost::edges(m_cfg); e_i != e_end; ++e_i){
		//Gets the map of the source and target flowpoints of the edge.
		FP_CFG_ID fID = boost::source(*e_i,m_cfg);
		FP_CFG_ID gID = boost::target(*e_i,m_cfg);
		VarToValue& srcState = fpStates[fID];
		VarToValue& tgtState = fpStates[gID];
		//compare each variable in the source to target.
		TransitionVariantSet transitionVariantSet = ComputeExprBlockInvariants(srcState,tgtState);
		//Gets the attached mc and adds Transition invariants to it
		MCWeakPtr mcWeak = boost::get(boost::edge_sizeChange,m_cfg,*e_i);
		MCSharedPtr mc = mcWeak.lock();
		ASSERT_LOOP_CONTINUE(mc != NULL);
		for(TransitionVariantSet::iterator transItr = transitionVariantSet.begin();
			transItr != transitionVariantSet.end();
			++transItr)
		{
			mc->addTrnasitionVariant(*transItr);
		}
	}
}
TransitionVariantSet CFGExprEvaluator::ComputeExprBlockInvariants(VarToValue& inValue, VarToValue& outValue) const
{
	TransitionVariantSet transitionVariantSet;
	//for all variable values at block end
	for (VarToValueIt outIt = outValue.begin(); outIt != outValue.end(); ++outIt)
	{
		//and for all variable values at block begin
		for (VarToValueIt inIt = inValue.begin(); inIt != inValue.end(); ++inIt)
		{
			ParamName var1 =(*inIt).first;
			ParamName var2 =(*outIt).first;
			//find order between 2 variable values
			Order o = ExprMgr::the().ComputeOrder(outValue[var2], inValue[var1], outValue);
			if (o != END_ORDER)
			{
				//order found, add invariant
				transitionVariantSet.insert(boost::make_tuple(var1, o, var2));
			}
		}
	}

	return transitionVariantSet;
}

