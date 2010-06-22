#pragma once
#include "snode.h"

class SForNode : public SNode
{
public:
	SForNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SForNode(void);
};
