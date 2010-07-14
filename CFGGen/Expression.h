#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <vector>
#include <map>
#include <string>
#include "boost\smart_ptr\shared_ptr.hpp"

//forward declaration 
class ExpressionInterface;
class Expression;

typedef std::string VarName;
typedef boost::shared_ptr<Expression> SPExpression;
typedef std::map<VarName,SPExpression> VarToValue;
typedef VarToValue::const_iterator VarToValueIt;

/**
*
* Expression evaluating class.
*
* The class supports binary addition, subtraction, multiplication, division,
* unary minus, parenthesis.
* 
*/

class Expression
{

public:
	enum ExprType {
		EXPR_TYPE_CONST,
		EXPR_TYPE_VAR,
		EXPR_TYPE_BINARY_OP,
		EXPR_TYPE_UNDEFINED
	};

	/**
	* Constructor.
	*/
	Expression()
	{
	}

	/**
	*
	* Evaluates the expression with a set of variable substitutions and
	* returns the result.
	*
	* @param value A mapping from variables to their values to substitute for the
	* variables the expression contains.
	*
	*/
	virtual SPExpression Evaluate(const VarToValue& value) const = 0;

	virtual ExprType Type() const = 0; 

	virtual SPExpression Clone() const = 0;
};

#endif