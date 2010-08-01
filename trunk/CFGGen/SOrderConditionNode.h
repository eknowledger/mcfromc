#include "SNode.h"
#include "SyntaxParserInterface.h"
#pragma once

class SOrderConditionNode :
	public SNode
{
public:
	SOrderConditionNode(const NodeData& data): SNode(data)
	{
	}
	~SOrderConditionNode(void);

	virtual bool IsOrderCondition() const {
		return true;
	}

	virtual bool IsValidExpression() {
		return isValidExpression(this);
	}

private:
	bool isValidExpression(SNode* subNode );
};
