#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include "boost\smart_ptr\shared_ptr.hpp"
#include "CommonDefs.h"

//forward declaration 
class ExpressionInterface;
class Expr;

typedef int ValType;
typedef boost::shared_ptr<Expr> SPExpr;
typedef std::map<ParamName,SPExpr> VarToValue;
typedef VarToValue::const_iterator VarToValueIt;

enum OperatorType
{
	OP_NOP,
	OP_MUL,
	OP_DIV,
	OP_ADD,
	OP_SUB,
	OP_MOD,
	OP_LESS,
	OP_LEQ,
	OP_EQ,
	OP_GREATER,
	OP_GEQ
};

enum ExprType {
	E_BINOP,
	E_ATOM
};

enum AtomType {
	A_NONE,
	A_CONST,
	A_VAR,
	A_UNDEF,
	A_ANY
};

//////////////////////////////////////////////////////////////////////////
/// The base expression class. Used for containment and evaluation of 
/// mathematical and order expressions.
//////////////////////////////////////////////////////////////////////////
class Expr
{
public:

	Expr()
	{
	}

	virtual SPExpr Evaluate(VarToValue& value) const = 0;
	virtual ExprType Type() const = 0; 
	virtual SPExpr Clone() const = 0;
	virtual void print(std::ostream& ostr) const = 0;

	virtual bool HasValue() const
	{
		return false;
	}
	virtual bool IsUndefined() const
	{
		return false;
	}
	virtual bool IsCondition() const
	{
		return false;
	}
	virtual bool IsVariable() const
	{
		return false;
	}

	virtual bool operator==(const Expr& rhs) const;
	virtual SPExpr operator*(const Expr& rhs) const;
	virtual SPExpr operator+(const Expr& rhs) const;
	virtual SPExpr operator-(const Expr& rhs) const;
	virtual SPExpr operator%(const Expr& rhs) const;
	virtual SPExpr operator/(const Expr& rhs) const;
};

#endif