#pragma once

#include "Expr.h"
#include "AtomExpr.h"
#include "BinExpr.h"
#include "exprsimplifier.h"

class SNode;

//////////////////////////////////////////////////////////////////////////
/// ExprMgr class is a singleton manager for various expression related
/// services. It provides method for creation of new expressions
//////////////////////////////////////////////////////////////////////////
class ExprMgr
{
public:
	static ExprMgr& the();
	~ExprMgr(void);

	SPExpr create(SNode* expressionNode);
	SPExpr createConst(ValType constValue);
	SPExpr createUndefined();
	SPExpr createVar(const ParamName& varName, ValType addedValue = 0);
	ExprSimplifier& Simplifier();
	Order ComputeOrder(const SPExpr& a, const SPExpr& b,VarToValue& v2v) const;
private:
	OperatorType OpType(SNode* node);

	ExprMgr();
	ExprMgr(const ExprMgr& other);
	ExprMgr& operator=(const ExprMgr& rhs);
	ExprSimplifier m_simplifier;
};
