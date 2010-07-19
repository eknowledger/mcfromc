#pragma once
#include "Expr.h"

class BinExpr;

class AtomExpr : public Expr
{
public:
	AtomExpr(ValType value);
	AtomExpr(const ParamName& name, bool isUndefined = false);
	AtomExpr(const AtomExpr& other);

	AtomExpr& operator=(const AtomExpr& rhs);
	bool operator==(const AtomExpr& rhs) const;
	
	virtual SPExpr operator*(const Expr& rhs) const;
	virtual SPExpr operator+(const Expr& rhs) const;
	virtual SPExpr operator-(const Expr& rhs) const;
	virtual SPExpr operator%(const Expr& rhs) const;
	virtual SPExpr operator/(const Expr& rhs) const;

	const ParamName& Name() const;
	ValType Value() const;

	virtual SPExpr Evaluate(const VarToValue& value) const;
	virtual ExprType Type() const;
	AtomType AType() const {
		return m_atomType;
	}
	virtual SPExpr Clone() const;
	virtual bool HasValue() const;
	virtual bool IsUndefined() const;
	virtual bool IsVariable() const
	{
		return !m_hasValue && !m_isUndefined;
	}
	virtual void print() const;
private:
	AtomType m_atomType;
	ParamName m_name;
	bool m_hasValue;
	bool m_isUndefined;
	ValType m_value;
};
