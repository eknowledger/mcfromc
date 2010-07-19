#pragma once
#include "Block.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////
/// This class represents an ordered set of consecutive flow points and
/// blocks.
//////////////////////////////////////////////////////////////////////////
class CompoundBlock : public Block
{
public:
	CompoundBlock(SNode* statement, FlowPoint* parent);
	virtual ~CompoundBlock();

	virtual FlowPointType Type() {
		return COMPOUND_BLOCK;
	}

	std::vector<FlowPoint*> ReduceExpressionsToBlocks();
};
