#include "SyntaxNodeFactory.h"
#include "SyntaxParserInterface.h"
#include "SExpressionNode.h"
#include "SForNode.h"
#include "SWhileNode.h"
#include "SDoWhileNode.h"
#include "SAssignmentNode.h"
#include "SIdentifierNode.h"
#include "SConstantNode.h"
#include "SIfElseNode.h"
#include "SReducibleNode.h"

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
			case CONDITION_IF:
			case CONDITION_IF_ELSE:
				ret = new SIfElseNode(*n);
				break;
			case STATEMENT_LIST:
			case STATEMENT:
			case COMPOUND_STATEMENT:
			case EXPRESSION_STATEMENT:
			case SELECTION_STATEMENT:
			case DECLARATION:
			case INIT_DECLARATOR_LIST:
			case PARAM_LIST:
			case PARAM_DECLARATION:
			case DECLARATION_LIST:
				ret = new SReducibleNode(*n);
				break;			
			default:
				ret = new SNode(*n);
				break;
		}
	}

	return ret;
}
