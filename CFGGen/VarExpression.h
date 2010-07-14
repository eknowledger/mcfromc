#pragma once
#include "expression.h"

class VarExpression :
	public Expression
{
public:
	VarName Name() {
		return m_name;
	}

	virtual SPExpression Evaluate(const VarToValue& value) const;

	virtual ExprType Type() const {
		return EXPR_TYPE_VAR;
	} 

	virtual SPExpression Clone() const;

private:
	friend class ExpressionFactory;
	VarExpression(VarName varName) : 
	   m_name(varName)
	{
	}

	VarName m_name;
};
