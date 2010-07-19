
#include "ForLoopFlowPoint.h"

ForLoopFlowPoint::ForLoopFlowPoint(SNode* _node, std::string _name, FlowPoint* incrementExpr):
	FlowPoint(_node, _name),
	m_incrementExpr(incrementExpr)
{
}

ForLoopFlowPoint::~ForLoopFlowPoint(void)
{
}
