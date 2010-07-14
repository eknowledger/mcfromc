
#include "BinaryOpExpression.h"
#include "constexpression.h"
#include "expressionfactory.h"

BinaryOpExpression::BinaryOpExpression(nodeType opType, 
									   const SPExpression& left, 
									   const SPExpression& right) :
	m_left(left),  m_right(right)
{
	switch (opType)
	{
	case ADD_EXPR:
		m_OpType = OP_ADD;
		break;
	case MULT_EXPR:
		m_OpType = OP_MUL;
		break;
	case SUB_EXPR:
		m_OpType = OP_SUB;
		break;
	case DIV_EXPR:
		m_OpType = OP_DIV;
		break;
	case MOD_EXPR:
		m_OpType = OP_MOD;
		break;
	default:
		m_OpType = OP_UNDEFINED;
		break;
	}
}

BinaryOpExpression::BinaryOpExpression(OperatorType opType, 
		const SPExpression& left, 
		const SPExpression& right) : 
	m_OpType(opType), 
	m_left(left), 
	m_right(right)
{
}

SPExpression BinaryOpExpression::Evaluate( const VarToValue& value ) const
{
	SPExpression res;
	if (areBothChildrenConst(m_left, m_right))
	{
		res = evaluateConstOperands(m_left, m_right);
	}
	else {
		SPExpression leftRes, rightRes;
		if (m_left->Type() == EXPR_TYPE_BINARY_OP) {
			SPExpression leftRes = m_left->Evaluate(value);
		}

		if (m_right->Type() == EXPR_TYPE_BINARY_OP) {
			rightRes = m_right->Evaluate(value);
		}

		if (leftRes.get() && rightRes.get()) {
			if (areBothChildrenConst(leftRes, rightRes))
			{
				res = evaluateConstOperands(leftRes, rightRes);
			}
		}
	}

	return res;
}

SPExpression BinaryOpExpression::evaluateConstOperands(const SPExpression& left, 
													   const SPExpression& right) const
{
	int newVal = 0;
	int leftVal = ((ConstExpression*)left.get())->ConstValue();
	int rightVal = ((ConstExpression*)right.get())->ConstValue();
	switch(m_OpType) 
	{
	case OP_ADD:
		newVal = leftVal + rightVal;
		break;
	case OP_SUB:
		newVal = leftVal - rightVal;
		break;
	case OP_DIV:
		newVal = leftVal / rightVal;
		break;
	case OP_MUL:
		newVal = leftVal * rightVal;
		break;
	case OP_MOD:
		newVal = leftVal % rightVal;
		break;
	}

	return ExpressionFactory::the().createConst(newVal);
}

bool BinaryOpExpression::areBothChildrenConst(const SPExpression& left,
											  const SPExpression& right) const
{
	return (left && right && left->Type() == EXPR_TYPE_CONST && 
			right->Type() == EXPR_TYPE_CONST);
}

SPExpression BinaryOpExpression::Clone() const
{
	SPExpression left = m_left->Clone();	
	SPExpression right = m_right->Clone();
	BinaryOpExpression* cloned = new BinaryOpExpression(m_OpType, left, right);
	return SPExpression(cloned);
}