#pragma once

#include "Expression.h"
#include "ConstExpression.h"

class SNode;

class ExpressionFactory
{
public:
	static ExpressionFactory& the();
	~ExpressionFactory(void);

	SPExpression create(SNode* expressionNode);
	SPExpression createConst(int constValue);
	SPExpression createUndefined();

private:
	void createChildren(SNode* expressionNode, SPExpression& left, SPExpression& right);
	ExpressionFactory();
	ExpressionFactory(const ExpressionFactory& other);
	ExpressionFactory& operator=(const ExpressionFactory& rhs);

};
