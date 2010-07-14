
#include "ConstExpression.h"

SPExpression ConstExpression::Clone() const
{
	return SPExpression(new ConstExpression(*this));
}