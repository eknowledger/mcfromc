#pragma once
#include "snode.h"

class SAssignmentNode : public SNode
{
public:
	SAssignmentNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SAssignmentNode(void);
};
