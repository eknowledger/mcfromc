
#include "UndefinedExpression.h"


SPExpression UndefinedExpression::Clone() const
{
	return SPExpression(new UndefinedExpression(*this));
}