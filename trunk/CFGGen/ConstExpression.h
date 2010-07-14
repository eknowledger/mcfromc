#pragma once
#include "expression.h"

class ConstExpression :
	public Expression
{
public:
	friend class ExpressionFactory;

	ConstExpression(int _constValue): m_constValue(_constValue) {}

	ConstExpression(const ConstExpression& other) : 
	m_constValue(other.m_constValue)
	{
	}

	ConstExpression& operator=(const ConstExpression& rhs)
	{
		m_constValue = rhs.m_constValue;
		return *this;
	}

	virtual SPExpression Evaluate(const VarToValue& value) const {
		return SPExpression(new ConstExpression(m_constValue));
	}

	int ConstValue() const {
		return m_constValue;
	}

	virtual ExprType Type() const {
		return EXPR_TYPE_CONST;
	} 

	virtual SPExpression Clone() const;

private:
	int m_constValue;
};
