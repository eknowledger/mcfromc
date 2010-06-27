#pragma once
#include "snode.h"

class SDoWhileNode : public SNode
{
public:
	SDoWhileNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SDoWhileNode(void);

	virtual bool ShouldCreateEdgeFromChildren() {
		return true;
	}
};
