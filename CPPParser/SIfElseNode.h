#pragma once
#include "snode.h"

class SIfElseNode : public SNode
{
public:
	SIfElseNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SIfElseNode(void);
};
