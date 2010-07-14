#pragma once
#include "expression.h"
#include "SyntaxParserInterface.h"

class BinaryOpExpression :
	public Expression
{
public:
	enum OperatorType {
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_UNDEFINED
	};

	const SPExpression& Left() {
	  return m_left;
	}

	const SPExpression& Right() {
	  return m_right;
	}

	OperatorType OpType() {
		return m_OpType;
	} 

	virtual ExprType Type() const {
		return EXPR_TYPE_BINARY_OP;
	} 

	virtual SPExpression Evaluate(const VarToValue& value) const;

	virtual SPExpression Clone() const;

private:
	friend class ExpressionFactory;

	BinaryOpExpression(nodeType opType, 
		const SPExpression& left, 
		const SPExpression& right);


	BinaryOpExpression(OperatorType opType, 
		const SPExpression& left, 
		const SPExpression& right);

	SPExpression evaluateConstOperands(const SPExpression& left, 
								   	   const SPExpression& right) const;

	bool areBothChildrenConst(const SPExpression& left,
							  const SPExpression& right) const;

	OperatorType m_OpType;
	SPExpression m_left;
	SPExpression m_right;
};
