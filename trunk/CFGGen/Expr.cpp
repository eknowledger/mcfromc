//=============================================================================
// Expression.cpp
//=============================================================================

#include "Expr.h"
#include "exprmgr.h"

bool Expr::operator==( const Expr& rhs ) const
{
	return false;
}

SPExpr Expr::operator*( const Expr& rhs ) const
{
	return ExprMgr::the().createUndefined();
}

SPExpr Expr::operator+( const Expr& rhs ) const
{
	return ExprMgr::the().createUndefined();
}

SPExpr Expr::operator-( const Expr& rhs ) const
{
	return ExprMgr::the().createUndefined();
}

SPExpr Expr::operator%( const Expr& rhs ) const
{
	return ExprMgr::the().createUndefined();	
}

SPExpr Expr::operator/( const Expr& rhs ) const
{
	return ExprMgr::the().createUndefined();
}