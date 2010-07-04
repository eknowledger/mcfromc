#include "SConstantNode.h"

SConstantNode::~SConstantNode(void)
{
}

void SConstantNode::printInfo(std::ostream& ostr) const 
{
	ostr << m_Value;
}