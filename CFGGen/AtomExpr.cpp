#include <ostream>
#include "AtomExpr.h"
#include "binexpr.h"
#include "exprmgr.h"

SPExpr AtomExpr::operator*( const Expr& _rhs ) const
{
	SPExpr res;
	

	if ((m_hasValue && Value() == 0) || 
		(_rhs.HasValue() && ((const AtomExpr&)_rhs).Value() == 0))
	{
		//if one of the sides is 0
		res = SPExpr(new AtomExpr(0));
	}
	else if  (m_hasValue)
	{
		if (_rhs.HasValue())
		{
			//if both sides has a numeric value - compute it.
			const AtomExpr& rhs = (const AtomExpr&)_rhs;
			res = SPExpr(new AtomExpr(m_value * rhs.Value())); 
		}
		else
		{
			//only left side has a numeric value - put is on the left side
			//of the multiplication (normal form - constant on the left).
			res = SPExpr(new BinExpr(OP_MUL, Clone(), _rhs.Clone()));	
		}
	}
	
	if (!res.get()) 
	{
		//either only the right side has numeric value of both doesn't.
		//Flip sides (normal form - constant on the left).
		res = SPExpr(new BinExpr(OP_MUL, _rhs.Clone(), Clone()));
	}

	return res;
}

bool AtomExpr::operator==( const AtomExpr& rhs ) const
{
	bool res = (m_hasValue == rhs.m_hasValue);
	if (res) {
		if (m_hasValue)
			res = (m_value == rhs.m_value);
		else
			res = (m_name == rhs.m_name);
	}

	return res;
}

bool AtomExpr::operator==( const Expr& rhs ) const
{
	bool rc = false;
	if (rhs.Type() == E_ATOM)
		rc = ((*this) == (const AtomExpr&)rhs);

	return rc;
}

AtomExpr& AtomExpr::operator=( const AtomExpr& rhs )
{
	m_name = rhs.m_name;
	m_hasValue = rhs.m_hasValue;
	m_value = rhs.m_value;
	return *this;
}

AtomExpr::AtomExpr( const AtomExpr& other ) : 
m_name(other.m_name), m_hasValue(other.m_hasValue), m_value(other.m_value),
m_isUndefined(other.m_isUndefined), m_atomType(other.m_atomType)
{

}

AtomExpr::AtomExpr( const ParamName& name, bool isUndefined ) :
m_name(name), m_hasValue(false), m_isUndefined(isUndefined)
{
	if (m_isUndefined)
		m_atomType = A_UNDEF;
	else
		m_atomType = A_VAR;
}

AtomExpr::AtomExpr( ValType value ) : 
m_value(value), m_hasValue(true), m_isUndefined(false), m_atomType(A_CONST)
{

}

const ParamName& AtomExpr::Name() const
{
	return m_name;
}

SPExpr AtomExpr::Evaluate( const VarToValue& value ) const
{
	SPExpr res;
	if (IsUndefined() || HasValue())
	{
		res = Clone();
	}
	else if (!HasValue()) {
		VarToValueIt it = value.find(m_name);
		if (it != value.end()) {
			res = (*it).second->Clone();
		}
	}

	if (!res.get()) {
		res = ExprMgr::the().createUndefined();
	}

	return res;
}

bool AtomExpr::HasValue() const
{
	return m_hasValue;
}

ValType AtomExpr::Value() const
{
	return m_value;
}

SPExpr AtomExpr::Clone() const
{
	return SPExpr(new AtomExpr(*this));
}

ExprType AtomExpr::Type() const
{
	return E_ATOM;
}

SPExpr AtomExpr::operator+( const Expr& _rhs ) const
{
	SPExpr res;

	if (_rhs.HasValue())
	{
		const AtomExpr& rhs = (const AtomExpr&)_rhs;
		if (m_hasValue) 
		{
			res = SPExpr(new AtomExpr(m_value + rhs.Value()));
		}
		else
		{
			res = SPExpr(new BinExpr(OP_ADD, Clone(), rhs.Clone()));	
		}

	}

	if (!res.get()) 
	{
		res = SPExpr(new BinExpr(OP_ADD, Clone(), _rhs.Clone()));
	}

	return res;
}


SPExpr AtomExpr::operator-( const Expr& _rhs ) const
{
	SPExpr res;

	if (_rhs.HasValue()) 
	{
		const AtomExpr& rhs = (const AtomExpr&)_rhs;
		if (m_hasValue)
		{
			res = SPExpr(new AtomExpr(m_value - rhs.Value())); 

		}
	}

	if (!res.get()) 
	{
		res = SPExpr(new BinExpr(OP_SUB, Clone(), _rhs.Clone()));
	}

	return res;
}

SPExpr AtomExpr::operator%( const Expr& rhs ) const
{
	SPExpr res;
	if (m_hasValue && rhs.HasValue())
	{
		res = ExprMgr::the().createConst(m_value % ((const AtomExpr&)rhs).Value());
	}
	else
	{
		res = ExprMgr::the().createUndefined();
	}

	return res;
}

SPExpr AtomExpr::operator/( const Expr& rhs ) const
{
	SPExpr res;
	if (m_hasValue && rhs.HasValue() && ((const AtomExpr&)rhs).Value() != 0)
	{
		res = ExprMgr::the().createConst(m_value / ((const AtomExpr&)rhs).Value());
	}
	else
	{
		res = ExprMgr::the().createUndefined();
	}

	return res;
}

bool AtomExpr::IsUndefined() const
{
	return false;
}

void AtomExpr::print(std::ostream& ostr) const
{
	if (AType() == A_CONST)
	{
		ostr << m_value;
	}
	else if (AType() == A_VAR|| AType() == A_UNDEF)
	{
		ostr << m_name;
	}
}