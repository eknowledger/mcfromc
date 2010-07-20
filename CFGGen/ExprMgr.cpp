#include "ExprMgr.h"
#include "SyntaxParserInterface.h"
#include "SNode.h"
#include "SConstantNode.h"
#include "SIdentifierNode.h"
#include <sstream>

ExprMgr::ExprMgr(void)
{
}

ExprMgr::~ExprMgr(void)
{
}

SPExpr ExprMgr::create( SNode* expressionNode )
{
	SPExpr res;
	if (expressionNode) {
		switch (expressionNode->Type())
		{
		case CONST_TYPE:
			res = SPExpr(new AtomExpr(((SConstantNode*)expressionNode)->value()));
			break;
		case ADD_EXPR:
		case SUB_EXPR:
		case MULT_EXPR:
		case DIV_EXPR:
		case MOD_EXPR:
		case LESS_THAN_EXPR:
		case LESS_EQ_THAN_EXPR:
		case EQUAL_EXPR:
		case GREATER_EQ_THAN_EXPR:
		case GREATER_THAN_EXPR:
			{
				SPExpr left = create(expressionNode->children()[0]);
				SPExpr right = create(expressionNode->children()[1]);
				res = SPExpr(new BinExpr(OpType(expressionNode), left, right));
			}
			break;
		case ID:
			res = SPExpr(new AtomExpr(((SIdentifierNode*)expressionNode)->name()));
			break;
		default:
			res = createUndefined();
			break;
		}
	}

	return res;
}

ExprMgr& ExprMgr::the()
{
	static ExprMgr theFactory;
	return theFactory;
}

SPExpr ExprMgr::createConst( ValType constValue )
{
	return SPExpr(new AtomExpr(constValue));
}

SPExpr ExprMgr::createUndefined()
{
	static size_t undefinedExprCounter = 0;
	std::ostringstream ostr;
	ostr << "'U_" << undefinedExprCounter;
	return SPExpr(new AtomExpr(ostr.str()));
}

OperatorType ExprMgr::OpType( SNode* node )
{
	OperatorType op = OP_ADD;
	switch(node->Type())
	{
	case MULT_EXPR:
		op = OP_MUL;
		break;
	case SUB_EXPR:
		op = OP_SUB;
		break;
	case DIV_EXPR:
		op = OP_DIV;
		break;
	case MOD_EXPR:
		op = OP_MOD;
		break;
	case ADD_EXPR:
		op = OP_ADD;
		break;
	case LESS_THAN_EXPR:
		op = OP_LESS;
		break;
	case LESS_EQ_THAN_EXPR:
		op = OP_LEQ;
		break;
	case EQUAL_EXPR:
		op = OP_EQ;
		break;
	case GREATER_EQ_THAN_EXPR:
		op = OP_GEQ;
		break;
	case GREATER_THAN_EXPR:
		op = OP_GREATER;
		break;
	}

	return op;
}

SPExpr ExprMgr::createVar(const ParamName& varName, ValType addedValue /*= 0*/ )
{
	SPExpr res = SPExpr(new AtomExpr(varName));
	if (addedValue != 0) {
		SPExpr add = SPExpr(new BinExpr(OP_ADD, res,createConst(addedValue)));
		res = add;
	}

	return res;
}

ExprSimplifier& ExprMgr::Simplifier()
{
	return m_simplifier;
}

Order ExprMgr::ComputeOrder(const SPExpr& a, const SPExpr& b, const VarToValue& v2v) const
{
	Order o = END_ORDER;
	SPExpr diff = *a - *b;
	SPExpr res = diff->Evaluate(v2v);
	if (res->HasValue())
	{
		ValType val = ((AtomExpr*)res.get())->Value();
		if (val > 0)
			o = GREATER;
		else if (val <0)
			o = LESS;
		else
			o = EQ;
	}

	return o;
}