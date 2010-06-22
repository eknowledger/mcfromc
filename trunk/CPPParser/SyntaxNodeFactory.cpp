#include "SyntaxNodeFactory.h"
#include "SyntaxParserInterface.h"
#include "SExpressionNode.h"
#include "SForNode.h"
#include "SWhileNode.h"
#include "SDoWhileNode.h"
#include "SAssignmentNode.h"
#include "SIdentifierNode.h"
#include "SConstantNode.h"

SyntaxNodeFactory::SyntaxNodeFactory(void)
{
}

SyntaxNodeFactory::~SyntaxNodeFactory(void)
{
}

SyntaxNodeFactory& SyntaxNodeFactory::the()
{
	static SyntaxNodeFactory theFactory;
	return theFactory;
}


SNode* SyntaxNodeFactory::createNode(NodeData* n)
{
	SNode* ret = NULL;
	if (n) {
		switch(n->m_type) {
			case EXPRESSION:
				ret = new SExpressionNode(*n);
				break;
			case DO_WHILE_LOOP:
				ret = new SDoWhileNode(*n);
				break;
			case WHILE_LOOP:
				ret = new SWhileNode(*n);
				break;
			case FOR_LOOP:
				ret = new SWhileNode(*n);
				break;
			case ASSIGNMENT_EXPR:
				ret = new SAssignmentNode(*n);
				break;
			case TYPE_SPECIFIER:
			case ID:
				ret = new SIdentifierNode(*n);
				break;
			case CONST_TYPE:
				ret = new SConstantNode(*n);
				break;
			default:
				ret = new SNode(*n);
				break;
		}
	}

	return ret;
}
