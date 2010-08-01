#include "SAssignmentNode.h"

SAssignmentNode::~SAssignmentNode(void)
{
}

bool SAssignmentNode::isValidExpression(SNode* subNode )
{
	bool rc =  (subNode && 
		subNode->Type() != POST_INCREMENT_EXPR &&
		subNode->Type() != POST_DECREMENT_EXPR &&
		subNode->Type() != PRE_INCREMENT_UNARY_EXPR &&
		subNode->Type() != PRE_DECREMENT_UNARY_EXPR);

	for (size_t i = 0; rc && i < subNode->children().size(); ++i) {
		rc = rc && isValidExpression(subNode->children()[i]);
	}

	return rc;
}