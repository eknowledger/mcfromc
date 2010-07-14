#pragma once
#include "expression.h"

class UndefinedExpression :
	public Expression
{
public:
	UndefinedExpression& operator=(const UndefinedExpression& rhs)
	{
		m_UndefinedValueId = rhs.m_UndefinedValueId;
		return *this;
	}

	UndefinedExpression(const UndefinedExpression& other) :
	m_UndefinedValueId(other.m_UndefinedValueId)
	{
	}

	bool operator==(const UndefinedExpression& rhs) const
	{
		return m_UndefinedValueId == rhs.m_UndefinedValueId;
	}

	virtual SPExpression Evaluate(const VarToValue& value) const {
		return SPExpression(new UndefinedExpression(*this));
	}

	virtual ExprType Type() const {
		return EXPR_TYPE_UNDEFINED;
	} 

	virtual SPExpression Clone() const;

private:
	friend class ExpressionFactory;
	UndefinedExpression(size_t newUndefinedValueId) : 
		m_UndefinedValueId(newUndefinedValueId)
	{
	}

	size_t m_UndefinedValueId;
};
