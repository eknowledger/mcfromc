#pragma once

#include <vector>
#include <hash_map>
#include "CompoundBlock.h"

class CFG;
class SNode;
class Block;
class FlowPoint;
typedef stdext::hash_map<SNode*,Block*>::iterator StatementMapIterator;

//////////////////////////////////////////////////////////////////////////
/// This class implements the algorithm of turning an Abstract Syntax Tree
/// to a Control Flow Graph.
//////////////////////////////////////////////////////////////////////////
class Syntax2CFG
{
public:
	/// Constructor - gets a root syntax node and a CFG on which to operate.
	Syntax2CFG(SNode* root, CFG& cfg);
	virtual ~Syntax2CFG();

	///The algorithm entry point
	bool execute();

private:
	FlowPoint* generateFlowPoints(SNode* root, FlowPoint* parent = NULL);
	FlowPoint* generateStatementNodeFlowPoints(SNode* root, FlowPoint* parent);
	FlowPoint* generateLoopNodeFlowPoints(SNode* root, FlowPoint* parent);
	FlowPoint* generateBranchNodeFlowPoints(SNode* root, FlowPoint* parent);

	FlowPoint* connectFlowPoints(FlowPoint* root,  
			 			         std::vector<FlowPoint*>& endFPs);	
	FlowPoint* connectFlowPointsInCompoundBlock(CompoundBlock* block,
										  std::vector<FlowPoint*>& endFPs);

	void reduceExpressionBlocks();

	Block* newCompoundBlock(SNode* statement, FlowPoint* parent);
	Block* newExpressionBlock(SNode* statement = NULL, FlowPoint* parent = NULL);	
	void concatVecs(std::vector<FlowPoint*>& a, const std::vector<FlowPoint*>& b);
	void clearCompoundBlocks();
	void hideIsolatedExpressions();

	
	stdext::hash_map<FlowPoint*, std::vector<FlowPoint*>> ChildrenOf;
	std::vector<FlowPoint*> m_compoundBlocks;

	SNode* m_root;
	CFG& m_cfg;
};
