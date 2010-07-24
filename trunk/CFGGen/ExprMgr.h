#pragma once

#include "Expr.h"
#include "AtomExpr.h"
#include "BinExpr.h"
#include "exprsimplifier.h"

class SNode;

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
	Order ComputeOrder(const SPExpr& a, const SPExpr& b, const VarToValue& v2v) const;
private:
	OperatorType OpType(SNode* node);

	ExprMgr();
	ExprMgr(const ExprMgr& other);
	ExprMgr& operator=(const ExprMgr& rhs);
	ExprSimplifier m_simplifier;
};