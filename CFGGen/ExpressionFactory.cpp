#include "ExpressionFactory.h"

#include "SyntaxParserInterface.h"
#include "SNode.h"
#include "SConstantNode.h"
#include "SIdentifierNode.h"

#include "undefinedexpression.h"
#include "binaryopexpression.h"
#include "varexpression.h"


ExpressionFactory::ExpressionFactory(void)
{
}

ExpressionFactory::~ExpressionFactory(void)
{
}

SPExpression ExpressionFactory::create( SNode* expressionNode )
{
	SPExpression res;
	if (expressionNode) {
		switch (expressionNode->Type())
		{
		case CONST_TYPE:
			res = SPExpression(new ConstExpression(((SConstantNode*)expressionNode)->value()));
			break;
		case ADD_EXPR:
		case SUB_EXPR:
		case MULT_EXPR:
		case DIV_EXPR:
		case MOD_EXPR:
			{
				SPExpression left, right;
				createChildren(expressionNode, left, right);
				res = SPExpression(new BinaryOpExpression(expressionNode->Type(), left, right));
			}
			break;
		case ID:
			res = SPExpression(new VarExpression(((SIdentifierNode*)expressionNode)->name()));
		default:
			res = createUndefined();
			break;
		}
	}

	return res;
}

ExpressionFactory& ExpressionFactory::the()
{
	static ExpressionFactory theFactory;
	return theFactory;
}

void ExpressionFactory::createChildren( SNode* expressionNode, SPExpression& left, SPExpression& right)
{
	left = create(expressionNode->children()[0]);
	right = create(expressionNode->children()[1]);
}

SPExpression ExpressionFactory::createConst( int constValue )
{
	return SPExpression(new ConstExpression(constValue));
}

SPExpression ExpressionFactory::createUndefined()
{
	static size_t undefinedExprCounter = 0;
	return SPExpression(new UndefinedExpression(undefinedExprCounter++));
}