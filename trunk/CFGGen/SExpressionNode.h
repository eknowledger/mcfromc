#pragma once
#include "snode.h"

class SExpressionNode : public SNode
{
public:
	SExpressionNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SExpressionNode(void);
};
