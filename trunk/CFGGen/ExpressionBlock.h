#pragma once
#include "Block.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////
/// This class represents an ordered set of consecutive expression 
/// flow points. It is a Flow Point by itself which is an abstraction of
/// consecutive O(1) commands to a single point in the CFG. 
//////////////////////////////////////////////////////////////////////////
class ExpressionBlock : public Block
{
public:
	ExpressionBlock(SNode* statement = NULL, FlowPoint* _parent = NULL);
	virtual ~ExpressionBlock();

	virtual FlowPointType Type() {
		return EXPRESSION_BLOCK;
	}

};
