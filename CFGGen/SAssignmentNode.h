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

	bool IsValidExpression() {
		return isValidExpression(this);
	}

	virtual ~SAssignmentNode(void);

private:
	bool isValidExpression(SNode* subNode);
};
