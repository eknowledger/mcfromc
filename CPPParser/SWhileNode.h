#pragma once
#include "snode.h"

class SWhileNode : public SNode
{
public:
	SWhileNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SWhileNode(void);
};
