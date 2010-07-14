#include "VarExpression.h"

SPExpression VarExpression::Evaluate( const VarToValue& value ) const
{
	SPExpression res;
	VarToValueIt it = value.find(m_name);
	if (it != value.end()) {
		res = (*it).second->Clone();
	}
	return res;
}

SPExpression VarExpression::Clone() const
{
	return SPExpression(new VarExpression(m_name));
}