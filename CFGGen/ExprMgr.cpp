#include "ExprMgr.h"
#include "SyntaxParserInterface.h"
#include "SNode.h"
#include "SConstantNode.h"
#include "SIdentifierNode.h"
#include <sstream>
#include "UniqueObjectIdMgr.h"

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
		case PREFIX_OP_UNARY_EXPR:
			{
				SPExpr right = create(expressionNode->children()[1]);
				switch (expressionNode->children()[0]->Type())
				{
				case PREFIX_PLUS:
					res = right;
					break;
				case PREFIX_MINUS:
					{
						SPExpr left = SPExpr(new AtomExpr(0));
						res = SPExpr(new BinExpr(OP_SUB, left, right));
					}
					break;
				case PREFIX_NOT:
					{
						if (right->HasValue())
						{
							ValType val = ((AtomExpr*)right.get())->Value() != 0 ? 0 : 1;
							res = SPExpr(new AtomExpr(val));
						}
						else {
							res = createUndefined();
						}
					}
					break;
				default:
					res = createUndefined();
					break;
				}

			}
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
	std::ostringstream ostr;
	ostr << "'U_" << UniqueObjectIdMgr::NewUndefinedValueId();
	return SPExpr(new AtomExpr(ostr.str(),true));
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

Order ExprMgr::ComputeOrder(const SPExpr& a, const SPExpr& b, VarToValue& v2v) const
{
	Order o = END_ORDER;
	SPExpr diff = *a - *b;
	ASSERT_RETURN(diff.get(), o);
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