#pragma once
#include "snode.h"

class SAssignmentNode : public SNode
{
public:
	SAssignmentNode(const NodeData& node): SNode(node)
	{
	}

	nodeType subType() {
		return children()[1]->Type();
	}

	virtual ~SAssignmentNode(void);
};
