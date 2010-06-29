#include "SyntaxUtils.h"
#include "SNode.h"

SyntaxUtils::SyntaxUtils(void)
{
}

SyntaxUtils::~SyntaxUtils(void)
{
}

bool SyntaxUtils::isStatement(SNode* node)
{
	return node->Type() == STATEMENT ||
		   node->Type() == TRANSLATION_UNIT;
}

bool SyntaxUtils::isLoop( SNode* node )
{
	bool rc = false;

	switch(node->Type()) {
		case WHILE_LOOP:
		case FOR_LOOP:
		case DO_WHILE_LOOP:
			rc = true;
			break;
	}

	return rc;
}

bool SyntaxUtils::isBranch( SNode* node )
{
	bool rc = false;

	switch(node->Type()) {
		case CONDITION_IF:
		case CONDITION_IF_ELSE:
			rc = true;
				break;
	}

	return rc;
}

bool SyntaxUtils::isForLoop( SNode* node )
{
	return node->Type() == FOR_LOOP;
}

bool SyntaxUtils::isDoWhileLoop( SNode* node )
{
	return node->Type() == DO_WHILE_LOOP;
}

bool SyntaxUtils::isWhileLoop( SNode* node )
{
	return node->Type() == WHILE_LOOP;
}

bool SyntaxUtils::isIfBranch( SNode* node )
{
	return node->Type() == CONDITION_IF;
}

bool SyntaxUtils::isIfElseBranch( SNode* node )
{
	return node->Type() == CONDITION_IF_ELSE;
}


bool SyntaxUtils::isExpressionsOnlyStatement( SNode* statementNode )
{
	bool rc = true;
	std::vector<SNode*>& children = statementNode->children();
	for (size_t i = 0; i < children.size() && rc; ++i) {
		rc = isExpression(children[i]);
	}

	return rc;
}

bool SyntaxUtils::isExpression( SNode* node )
{
	nodeType type = node->Type();
	return 	type == ASSIGNMENT_EXPR || 
			type == POST_DECREMENT_EXPR || 
			type == POST_INCREMENT_EXPR;
}



