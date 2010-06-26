#pragma once
#include "snode.h"

class SReducibleNode : public SNode
{
public:
	SReducibleNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SReducibleNode(void);

	virtual bool ShouldBeReduced();
};
