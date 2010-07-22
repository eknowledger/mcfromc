#include <ostream>
#include "BinExpr.h"
#include "atomexpr.h"
#include "exprmgr.h"

SPExpr BinExpr::Evaluate( const VarToValue& value ) const
{
	SPExpr res;

	SPExpr left = m_left->Evaluate(value);
	SPExpr right = m_right->Evaluate(value);

	switch(m_OpType)
	{
	case OP_ADD:
		res = *left + *right;
		break;
	case OP_SUB:
		res = *left - *right;
		break;
	case OP_DIV:
		res = *left / *right;
		break;
	case OP_MUL:
		res = *left * *right;
		break;
	case OP_MOD:
		res = *left % *right;
		break;	
	}
	
	if (!res.get())
	{
		res = SPExpr(new BinExpr(m_OpType, left, right));
	}
	bool wasSimplified = false; 
	res = ExprMgr::the().Simplifier().Simplify(res, wasSimplified);
	if (wasSimplified)
	{
		res = res->Evaluate(value);
	}

	return res;
}

bool BinExpr::operator==( const Expr& rhs ) const
{
	bool rc = (rhs.Type() == E_BINOP);
	if (rc) {
		const BinExpr& brhs = (const BinExpr&)rhs;
		rc = m_OpType == brhs.OpType() &&
		     *m_left == *(brhs.Left()) &&
		     *m_right == *(brhs.Right());
	}

	return rc;
}

BinExpr& BinExpr::operator=( const BinExpr& rhs )
{
	m_left = rhs.m_left->Clone();
	m_right = rhs.m_right->Clone();
	m_OpType = rhs.m_OpType;

	return *this;
}

BinExpr::BinExpr( const BinExpr& other ) : 
m_left(other.m_left->Clone()), m_right(other.m_right->Clone()),
m_OpType(other.m_OpType)
{

}

BinExpr::BinExpr( OperatorType opType, SPExpr left, SPExpr right ) :
m_left(left), m_right(right), m_OpType(opType)
{

}

SPExpr BinExpr::Clone() const
{
	return SPExpr(new BinExpr(m_OpType, m_left->Clone(), m_right->Clone()));
}

SPExpr BinExpr::operator+( const Expr& rhs ) const
{
	return SPExpr(new BinExpr(OP_ADD, Clone(), rhs.Clone()));
}

SPExpr BinExpr::operator-( const Expr& rhs ) const
{
	return SPExpr(new BinExpr(OP_SUB, Clone(), rhs.Clone()));
}

SPExpr BinExpr::operator*( const Expr& rhs ) const
{
	SPExpr res;
	if (rhs.HasValue()) 
	{
		//if rhs expression is the constant zero - the expression
		//evaluates to zero.
		const AtomExpr& atom = (const AtomExpr&)rhs;
		if (atom.Value() == 0)
			res = SPExpr(new AtomExpr(0));
	}

	if (!res.get())
	{
		res = SPExpr(new BinExpr(OP_MUL, Clone(), rhs.Clone()));
	}

	return res;
}

bool BinExpr::IsCondition() const
{
	return m_OpType == OP_LESS || m_OpType == OP_LEQ || 
		   m_OpType == OP_EQ || m_OpType == OP_GEQ ||
		   m_OpType == OP_GREATER;
}

void BinExpr::print(std::ostream& ostr) const
{
	std::string op;
	if (m_OpType == OP_ADD)
		op = "+";
	else if (m_OpType == OP_SUB)
		op = "-";
	else if (m_OpType == OP_MUL)
		op = "*";
	else if (m_OpType == OP_DIV)
		op = "/";
	else if (m_OpType == OP_MOD)
		op = "%";
	else if (m_OpType == OP_LESS)
		op = "<";
	else if (m_OpType == OP_LEQ)
		op = "<=";
	else if (m_OpType == OP_EQ)
		op = "==";
	else if (m_OpType == OP_GEQ)
		op = ">=";
	else if (m_OpType == OP_GREATER)
		op = ">";
	ostr << "(";
	m_left->print(ostr);
	ostr << op;
	m_right->print(ostr);
	ostr << ")";
}