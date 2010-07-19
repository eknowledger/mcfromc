#pragma once
#include "flowpoint.h"

class ForLoopFlowPoint :
	public FlowPoint
{
public:
	ForLoopFlowPoint(SNode* node, std::string name, FlowPoint* incrementExpr);
	virtual ~ForLoopFlowPoint(void);

	FlowPoint* getIncrementExpression() {
		return m_incrementExpr;
	}

	virtual FlowPointType Type() {
		return FOR_LOOP_FLOW_POINT;
	}


private:
	//the increment expression of the for loop declaration
	FlowPoint* m_incrementExpr;
};
