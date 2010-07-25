#pragma once

#include "Expr.h"
#include "CommonGraphDefs.h"


//////////////////////////////////////////////////////////////////////////
/// Holds a binary operator expression. 
/// Supports regular math operators: +,-,*,/,% 
/// and also order expressions: <, <=, =, >=, >.
//////////////////////////////////////////////////////////////////////////
class BinExpr : 
	public Expr
{
public:

	BinExpr(OperatorType opType, SPExpr left, SPExpr right);

	BinExpr(const BinExpr& other);

	BinExpr& operator=(const BinExpr& rhs);

	bool operator==(const Expr& rhs) const;
	virtual SPExpr operator*(const Expr& rhs) const;
	virtual SPExpr operator+(const Expr& rhs) const;
	virtual SPExpr operator-(const Expr& rhs) const;

	OperatorType OpType() const
	{
		return m_OpType;
	}

	const SPExpr& Left() const {
		return m_left;
	}

	const SPExpr& Right() const {
		return m_right;
	}

	virtual SPExpr Evaluate(VarToValue& value) const;

	virtual ExprType Type() const 
	{
		return E_BINOP;
	}
	virtual SPExpr Clone() const;
	virtual bool IsCondition() const;
	virtual void print(std::ostream& ostr) const;

private:
	OperatorType m_OpType;
	SPExpr m_left;
	SPExpr m_right;

};
