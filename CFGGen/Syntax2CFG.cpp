#include "Syntax2CFG.h"
#include "CFG.h"
#include "SyntaxSimplifier.h"
#include "SNode.h"
#include "Block.h"
#include "CompoundBlock.h"
#include "ExpressionBlock.h"
#include "SyntaxUtils.h"
#include <iostream>
#include "forloopflowpoint.h"
#include "SIdentifierNode.h"

namespace{
	void addTransition(FlowPoint* f,FlowPoint* g,CFG& cfg, bool isInvariantTrue = false){
		if(!cfg.isEdge(f,g)){
			cfg.AddEdge(f,g);
			cfg.MarkEdgeAsInvariantTrue(f,g, isInvariantTrue);
		}
	}
}

Syntax2CFG::Syntax2CFG(SNode* root, CFG& cfg):
	m_root(root), m_cfg(cfg)
{
}

Syntax2CFG::~Syntax2CFG()
{
	clearCompoundBlocks();
}

/// Description: The starting point of the algorithm
/// Return value: bool - success / failure.
bool Syntax2CFG::execute()
{
	bool rc = false;
	clearCompoundBlocks();
	ChildrenOf.clear();
	SyntaxSimplifier(m_root).execute();
	collectVariableNames(m_root);
	FlowPoint* fp = generateFlowPoints(m_root);
	if (fp) {
		reduceExpressionBlocks();
		std::vector<FlowPoint*> endFPs;
		connectFlowPoints(fp, endFPs);
		mergeConsecutiveExpressionBlocks();
		if (m_compoundBlocks.size() > 0)
			m_cfg.SetStart(((Block*)m_compoundBlocks[0])->flowPoints()[0]);
		rc = true;
	}

	return rc;
}

/// Description: Connects all flow points from root FP and below.
/// Params:
///		[in]  root - the root flow point on which to operate.
///		[out] endFPs - will contain all FPs which should be connected to
///					   next flow points in parent scope.
/// Return value: A Flow Point which should be connected
///				  from previous ending flow points in parent scope.
FlowPoint* Syntax2CFG::connectFlowPoints(FlowPoint* root, 
										 std::vector<FlowPoint*>& endFPs)
{	
	FlowPoint* startFP = NULL;
	endFPs.clear();

	if (root) {
		if (root->Type() == FlowPoint::EXPRESSION_BLOCK) {
			startFP = root;
			endFPs.push_back(root);
		}
		else if (root->Type() == FlowPoint::COMPOUND_BLOCK) {
			startFP = connectFlowPointsInCompoundBlock((CompoundBlock*)root, endFPs);
		}
		else {
			std::vector<FlowPoint*>& children = ChildrenOf[root];
			if (children.size() == 0) { //if no children
				startFP = root;
				endFPs.push_back(root);
				if (root->syntaxNode() && root->syntaxNode()->ShouldCreateEdgeFromChildren()) {
					if (root->Type() == FlowPoint::FOR_LOOP_FLOW_POINT)
					{
						//Connect increment expression to for loop node.
						//Later all end points will be connected to the increment expression.
						FlowPoint* incrFP = ((ForLoopFlowPoint*)root)->getIncrementExpression();
						addTransition(incrFP, root, m_cfg);
						addTransition(root, incrFP, m_cfg);
					}
					else {
						addTransition(root,root,m_cfg);
					}
				}
			}
			for (size_t i = 0; i < children.size(); ++i) {
				FlowPoint* currStartFP = NULL;
				std::vector<FlowPoint*> currEndFPs;
				currStartFP = connectFlowPoints(children[i], currEndFPs);
				if (currStartFP) {
					bool markTransitionAsInvariantTrue = root->syntaxNode() &&
						( SyntaxUtils::isLoop(root->syntaxNode())          ||
						  SyntaxUtils::isIfBranch(root->syntaxNode())      ||
						  ( SyntaxUtils::isIfElseBranch(root->syntaxNode()) && i == 0)
						 );
					//add downstream edge
					addTransition(root,currStartFP,m_cfg, markTransitionAsInvariantTrue);
				}

				bool concatEndFPs = true;

				if (root->syntaxNode()) {					
					//check for loop FP
					if (root->syntaxNode()->ShouldCreateEdgeFromChildren()) {
						
						FlowPoint* nodeToConnect = root;
						if (root->Type() == FlowPoint::FOR_LOOP_FLOW_POINT)
						{
							//Connect increment expression to for loop node.
							//Later all end points will be connected to the increment expression.
							nodeToConnect = ((ForLoopFlowPoint*)root)->getIncrementExpression();
							addTransition(nodeToConnect, root, m_cfg);
						}

						// loop flow point - connect leaves to it
						for (size_t j = 0; j < currEndFPs.size(); ++j) {
							addTransition(currEndFPs[j],nodeToConnect,m_cfg);
						}

						if (SyntaxUtils::isDoWhileLoop(root->syntaxNode()) &&
							currStartFP)
						{
							//Do while loop - connect loop FP to 1st FP in
							//its inner block and return the 1st FP to the upper level.
							startFP = currStartFP;
							endFPs.push_back(root);
							//addTransition(root, startFP, m_cfg, true);
						}
						else
						{
							//make sure that loop FP is connected to next&prev FP by
							//adding the loop FP to the end vector and setting the
							//start FP to it.
							//In this case, any FPs inside the loop statement
							//should not be passed to the parent scope.
							endFPs.push_back(root);
							startFP = root;
						}
						concatEndFPs = false;
					}
					else if (SyntaxUtils::isBranch(root->syntaxNode())) {
						//if it's an if / if else branch, return the FP
						//as the start FP.
						startFP = root;
						if (SyntaxUtils::isIfBranch(root->syntaxNode())) {
							//if it's an 'if' branch(no else), add the FP
							//also to the end FPs vector (it needs to be connected
							//to the next FP in the parent scope).
							endFPs.push_back(root);
						}
						//End FPs should be passed to the parent scope.
					}
				}

				if (concatEndFPs) {
					concatVecs(endFPs, currEndFPs);
				}
			}
		}
	}

	return startFP;
}

/// Description: Connects all flow points from within a compound block.
///              A compound block is defined to be an ordered set of commands which 
///              are consecutive in the program flow.
/// Params:
///		[in]  block - the compound block on which to operate.
///		[out] endFPs - will contain all FPs which should be connected to
///					   next flow points in parent scope.
/// Return value: A Flow Point which should be connected
///				  from previous ending flow points in parent scope.
FlowPoint* Syntax2CFG::connectFlowPointsInCompoundBlock(CompoundBlock* block,
													    std::vector<FlowPoint*>& endFPs)
{
	FlowPoint* startFP = NULL;
	endFPs.clear();
	std::vector<FlowPoint*> fps = block->flowPoints();
	std::vector<FlowPoint*> prevEndFPs;
	
	//for each flow point in block
	for (size_t i = 0; i < fps.size(); ++i) {
		FlowPoint* currStartFP = NULL;
		std::vector<FlowPoint*> currEndFPs;
	
		//connect it's sub tree flow points
		currStartFP = connectFlowPoints(fps[i], currEndFPs);

		//for each ending flow point of the previous flow point sub-tree 
		for (size_t j = 0; j < prevEndFPs.size(); ++j) {
			//if current flow point is a simple FP or an expression block
			if ((fps[i]->Type() == FlowPoint::FLOW_POINT ||
				fps[i]->Type() == FlowPoint::EXPRESSION_BLOCK) &&
				!SyntaxUtils::isDoWhileLoop(fps[i]->syntaxNode())) {
				//if next node is a FP or Expression Block, connect directly to it,
				addTransition(prevEndFPs[j],fps[i],m_cfg);
			}
			else {
				//otherwise, current FP is actually a compound block.
				//connect all previous end FP's to current node start FP.
				addTransition(prevEndFPs[j],currStartFP,m_cfg);
			}
		}	
		
		//the general block starting Flow Points are the ones produced by
		//analyzing the sub-tree of the 1st FP in the block.
		if (i == 0) {
			startFP = currStartFP;
		}	
		//the general block ending Flow Points are the ones produced by
		//analyzing the sub-tree of the last FP in the block.
		if (i == fps.size()-1) {
			endFPs = currEndFPs;
		}

		//keep previous ending flow points in order to connect to next FP
		//in block in the next iteration.
		prevEndFPs = currEndFPs;
	}

	return startFP;
}

/// Description: Generates:
///					1. flow points for commands.
///					2. Expression blocks for statements containing only expressions.
///					3. Compound blocks for statements containing expressions and
///					   other commands.
///              Maps ChildrenOf relation between each Flow Point/Block and it's
///              children in the AST.
/// Params:
///		[in]  root - the syntax node root to generate it's subtree FPs.
///		[in] parent  - parent FP of the current subtree uppermost FP.
/// Return value: The uppermost Flow Point generated for the given subtree.
FlowPoint* Syntax2CFG::generateFlowPoints(SNode* root, FlowPoint* parent)
{	
	FlowPoint* ret = NULL;
	if (SyntaxUtils::isStatement(root) || root->Type() == EXPRESSION) {
		ret = generateStatementNodeFlowPoints(root, parent);
	}
	else if (SyntaxUtils::isExpression(root)) {
		ret = m_cfg.AddHiddenFlowPoint(root, "Expression");
	}
	else if (SyntaxUtils::isLoop(root)) {
		ret = generateLoopNodeFlowPoints(root, parent);
	}
	else if (SyntaxUtils::isBranch(root)) {
		ret = generateBranchNodeFlowPoints(root, parent);
	}

	if (ret && parent) {
		ChildrenOf[parent].push_back(ret);
	}

	return ret;
}

FlowPoint* Syntax2CFG::generateStatementNodeFlowPoints(SNode* root, FlowPoint* parent)
{
	FlowPoint* ret = NULL;
	Block* b = NULL;
	if (SyntaxUtils::isExpressionsOnlyStatement(root)) {
		b = newExpressionBlock(root, parent);
	}
	else if (root->children().size() > 1 || 
		     (root->children().size() == 1 && 
		      root->children().front()->Type() == FOR_LOOP) ) {
		//only generate compound block if there is more than one child,
	    //or if single child is a for loop node.
		b = newCompoundBlock(root, parent);
	}

	std::vector<SNode*>& children = root->children();

	if (b) {
		//block was generated. Populate it with flow points.
		for (std::vector<SNode*>::iterator it = children.begin();
			it !=  children.end(); ++it) {
				FlowPoint* fp = generateFlowPoints(*it, b);
				if (fp) {
					b->Add(fp);
				}
		}

		ret = b;
	}
	else if (!children.empty()) {
		//there is only one child, generate flow points for it's subtree.
		//No need to create a block for a single child node !
		ret = generateFlowPoints(children[0], parent);
	}

	return ret;
}

FlowPoint* Syntax2CFG::generateLoopNodeFlowPoints(SNode* root, FlowPoint* parent)
{
	FlowPoint* fp = NULL;
	if (SyntaxUtils::isForLoop(root)) {
		FlowPoint* assignExpr = generateFlowPoints(root->children()[0], parent);
		((Block*)parent)->Add(assignExpr);
		FlowPoint* loopIncr = generateFlowPoints(root->children()[2]);
		Block* b = NULL;
		if (loopIncr->Type() != FlowPoint::EXPRESSION_BLOCK) {
			b = newExpressionBlock(NULL, NULL);
			b->Add(loopIncr);
		}
		else {
			b = (Block*)loopIncr;
		}
		ForLoopFlowPoint* forLoop = new ForLoopFlowPoint(root, "For Loop", b);
		generateFlowPoints(root->children()[3], forLoop);
		m_cfg.AddFlowPoint(forLoop);
		fp = forLoop;
	}
	else if (SyntaxUtils::isWhileLoop(root)) {
		fp = m_cfg.AddFlowPoint(root, "While Loop");
		generateFlowPoints(root->children()[1], fp);
	}
	else if (SyntaxUtils::isDoWhileLoop(root)) {
		fp = m_cfg.AddFlowPoint(root, "Do While Loop");
		generateFlowPoints(root->children()[0], fp);
	}

	return fp;
}

FlowPoint* Syntax2CFG::generateBranchNodeFlowPoints( SNode* root, FlowPoint* parent )
{
	FlowPoint* fp = NULL;
	if (SyntaxUtils::isIfBranch(root)) {
		fp = m_cfg.AddFlowPoint(root, "If Branch");
		generateFlowPoints(root->children()[1], fp);
	}
	else if (SyntaxUtils::isIfElseBranch(root)) {
		fp = m_cfg.AddFlowPoint(root, "If Else Branch");
		generateFlowPoints(root->children()[1], fp);
		generateFlowPoints(root->children()[2], fp);
	}

	return fp;
}

/// Description: Goes over all compound blocks and replaces any consecutive 
///         sequence of Expression FP's with an Expression Block containing 
///         this sequence.
void Syntax2CFG::reduceExpressionBlocks()
{
	size_t nBlocks = m_compoundBlocks.size();
	for (size_t i = 0; i < nBlocks; ++i) {
		if (m_compoundBlocks[i]->Type() == FlowPoint::COMPOUND_BLOCK) {
			std::vector<FlowPoint*> newBlocks = 
				((CompoundBlock*)m_compoundBlocks[i])->ReduceExpressionsToBlocks();
			for (size_t j = 0; j < newBlocks.size(); ++j) {
				m_cfg.AddFlowPoint(newBlocks[j]);
			}
		}
	}
}

/// Description: Creates a new compound block from the Statement syntax node
///       and adds it to the m_blocks vector.
/// Params:
///		[in]  statement - the statement syntax node which will be assigned to
///                       the block.
///		[int] parent  - the parent scope flow point of the compound block.
/// Return value: The new compound block.
Block* Syntax2CFG::newCompoundBlock(SNode* statement, FlowPoint* parent)
{
	Block* b = new CompoundBlock(statement, parent);
	m_compoundBlocks.push_back(b);
	return b;
}

/// Description: Creates a new expression block from the Statement syntax node
///       and adds it to the CFG.
/// Params:
///		[in]  statement - the statement syntax node which will be assigned to
///                       the block.
///		[int] parent  - the parent scope flow point of the expression block.
/// Return value: The new expression block.
Block* Syntax2CFG::newExpressionBlock(SNode* statement, FlowPoint* parent)
{
	Block* b = new ExpressionBlock(statement, parent);
	m_cfg.AddFlowPoint(b);
	return b;
}


/// Description: Concatenates vector b to the end of vector a.
void Syntax2CFG::concatVecs(std::vector<FlowPoint*>& a, const std::vector<FlowPoint*>& b)
{
	a.reserve(a.size() + b.size());
	for (size_t i = 0; i < b.size(); ++i) {
		a.push_back(b[i]);
	}
}

/// Description: Deletes compound blocks and clears the blocks array.
void Syntax2CFG::clearCompoundBlocks()
{
	for (size_t i = 0; i < m_compoundBlocks.size(); ++i) {
		//delete only compound blocks since they are not added to the CFG.
		delete m_compoundBlocks[i];
	}
	m_compoundBlocks.clear();
}

/// Merges expression blocks which are consecutive in the CFG - 
/// e.g. there is an edge from Expr. Block A to Expr. Block B, and there are
/// no other in edges to Expr. Block B. In this case, Expr. Block B can be merged 
/// into Expr. Block A.
void Syntax2CFG::mergeConsecutiveExpressionBlocks()
{
	std::vector<FlowPoint*> fps = m_cfg.flowPoints();
	for (size_t i = 0; i < fps.size(); ++i)
	{
		if (fps[i]->Type() == FlowPoint::EXPRESSION_BLOCK)
		{

			FlowPointList ancestors = m_cfg.ancestors(fps[i]);
			//If there is exactly one ancestor, and it is also an expression block
			if (ancestors.size() == 1 &&
				ancestors.front()->Type() == FlowPoint::EXPRESSION_BLOCK) 
			{
				Block* first = (Block*)ancestors.front();
				Block* second = (Block*)fps[i];
				//copy all expressions from second block to first block
				const std::vector<FlowPoint*>& secondExprBlockFps = second->flowPoints();
				for (size_t j = 0; j < secondExprBlockFps.size(); ++j)
				{
					first->Add(secondExprBlockFps[j]);
				}
				//remove edge between 2 blocks
				m_cfg.RemoveEdge(first,second);
				//add edge from first block to all neighbors of second block
				FlowPointList predecessors = m_cfg.neighbors(second);
				;
				for (FlowPointList::iterator it = predecessors.begin(); it != predecessors.end(); ++it)
				{
					m_cfg.RemoveEdge(second, *it);
					m_cfg.AddEdge(first, *it);
				}
				//finally, remove second block from CFG.
				m_cfg.RemoveFlowPoint(second);				
			}
		}
	}
}

void Syntax2CFG::collectVariableNames( SNode* root )
{
	if (root)
	{
		if (root->Type() == ID) 
		{
			m_cfg.AddVariable(((SIdentifierNode*)root)->name());
		}

		for (size_t i = 0; i < root->children().size(); ++i)
		{
			collectVariableNames(root->children()[i]);
		}
	}
}