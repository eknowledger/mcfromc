
#include "CFGExprEvaluator.h"
#include "SyntaxUtils.h"
#include "SNode.h"
#include <vector>
#include "SIdentifierNode.h"
#include "Block.h"
#include "boost\graph\depth_first_search.hpp"


void CFGExprEvaluator::Evaluate()
{
	ExprEvalVisitor vis;
	if (m_cfg.Start())
	{
		FP_CFG_ID s = m_cfg.Start()->cfgID();
		boost::depth_first_visit(m_cfg, s, vis, get(boost::vertex_color, m_cfg));
	}
	else
	{
		//no starting point set - do regular dfs
		boost::depth_first_search(m_cfg, boost::visitor(vis));
	}
}

std::wstring CFGExprEvaluator::ExprEvalVisitor::StringToWString(const std::string& s) const
{
	std::wstring temp(s.length(),L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp; 
}




template <typename Edge, typename Graph>
void CFGExprEvaluator::ExprEvalVisitor::examine_edge( Edge u, const Graph& g )
{
	//copy value map from source-out to target-in.
	FP_CFG_ID s = boost::source(u,g);
	FP_CFG_ID t = boost::target(u,g);
	FPointWeakPtr wpSrcFP = boost::get(boost::vertex_attachedFP,g,s);
	FPointWeakPtr wpTgtFP = boost::get(boost::vertex_attachedFP,g,t);
	FlowPoint* srcFP = wpSrcFP.lock().get();
	FlowPoint* tgtFP = wpTgtFP.lock().get();
	if (srcFP && tgtFP)
	{
		//TODO: copy out VarToValue map to in VarToValue map:
		//tgtFP->InValue() = srcFP->OutValue();
	}
}

template < typename Vertex, typename Graph >
void CFGExprEvaluator::ExprEvalVisitor::discover_vertex( Vertex u, const Graph & g ) const
{
	FPointWeakPtr wpFP = boost::get(boost::vertex_attachedFP,g,u);
	FlowPoint* fp = wpFP.lock().get();

	if (fp)
	{
		//TODO: copy in VarToValue map to out VarToValue map:
		//fp->OutValue() = fp->InValue();
		if (fp->Type() == FlowPoint::EXPRESSION_BLOCK)
		{

			//serially evaluate expressions, updating the out values map.
			const std::vector<FlowPoint*>& exprsFPs = ((Block*)fp)->flowPoints(); 
			for (size_t i = 0; i < exprsFPs.size(); ++i)
			{
				evaluateExprFlowPoint(fp, exprsFPs[i]);
			}
			//fp->SizeChange() = ComputeExprBlockInvariants(fp->InValue(), fp->OutValue());

		}
		else {
			evaluateBranchInvariants(fp);
		}
	}
}

void CFGExprEvaluator::ExprEvalVisitor::evaluateExprFlowPoint(FlowPoint* expressionBlock, FlowPoint* fp) const
{
	SNode* expr = fp->syntaxNode();
	if (expr && expr->children().size() > 0)
	{
		ParamName var;
		SPExpr val;
		SNode* identNode = expr->children()[0];
		if (identNode && identNode->Type() == ID)
		{					
			var = ((SIdentifierNode*)expr->children()[0])->name();
			if (expr->Type() == ASSIGNMENT_EXPR)
			{
				val = ExprMgr::the().create(expr->children()[1]);
			}
			else if (expr->Type() == POST_INCREMENT_EXPR ||
				expr->Type() == PRE_INCREMENT_UNARY_EXPR)
			{
				val = ExprMgr::the().createVar(var, 1);
			}
			else if (expr->Type() == POST_DECREMENT_EXPR ||
				expr->Type() == PRE_DECREMENT_UNARY_EXPR)
			{
				val = ExprMgr::the().createVar(var, -1);
			}
			else
			{
				val = ExprMgr::the().createUndefined();
			}

			if (val.get())
			{	
				//TODO - add assignment to VarToValue map:
				//expressionBlock->OutValue()[var] = val->Evaluate(expressionBlock->OutValue());
			}
		}
	}
}

void CFGExprEvaluator::ExprEvalVisitor::findRelevantSubConditions(SNode* node, std::vector<SNode*>& subConditions) const
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

void CFGExprEvaluator::ExprEvalVisitor::evaluateBranchInvariants( FlowPoint* fp ) const
{
	if (fp->syntaxNode())
	{
		SNode* node = fp->syntaxNode();
		SNode* condition = NULL;
		if (node->Type() == WHILE_LOOP ||
			node->Type() == CONDITION_IF ||
			node->Type() == CONDITION_IF_ELSE)
		{
			condition = node->children()[0];
		}
		else if (node->Type() == DO_WHILE_LOOP ||
			node->Type() == FOR_LOOP)
		{
			condition = node->children()[1];
		}

		if (condition)
		{
			std::vector<SNode*> subConditions;
			findRelevantSubConditions(condition, subConditions);
			for (size_t i = 0; i < subConditions.size(); ++i)
			{
				SPExpr orderCond = ExprMgr::the().create(subConditions[i]);
				if (orderCond.get())
				{
					InvariantMember inv = computeExprInvariant((const BinExpr&)*orderCond);
					//TODO - put the invariant on the MC graph
				}
			}
		}
	}
}

InvariantMember CFGExprEvaluator::ExprEvalVisitor::computeExprInvariant( const BinExpr& expr ) const
{
	if (expr.IsCondition())
	{
		SPExpr left = expr.Left();
		SPExpr right = expr.Right();
		if (left->IsVariable() && right->IsVariable())
		{
			std::wstring wsLeft = StringToWString(((AtomExpr*)left.get())->Name());
			std::wstring wsRight = StringToWString(((AtomExpr*)right.get())->Name());
			return InvariantMember(wsLeft, order(expr.OpType()), wsRight);	
		}
	}

	return InvariantMember(L"", END_ORDER,L"");
}

Order CFGExprEvaluator::ExprEvalVisitor::order( OperatorType opType ) const
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

Invariant CFGExprEvaluator::ExprEvalVisitor::ComputeExprBlockInvariants( 
														 VarToValue& inValue, 
														 VarToValue& outValue ) const
{
	Invariant inv;
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
				inv.insert(InvariantMember(StringToWString(var1), o, StringToWString(var2)));
			}
		}
	}

	return inv;
}