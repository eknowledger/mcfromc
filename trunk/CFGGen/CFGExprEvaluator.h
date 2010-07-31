#pragma once

#include "CFG.h"
#include "ExprMgr.h"
#include <boost/graph/depth_first_search.hpp>
#include <vector>
#include "CommonGraphDefs.h"

class FlowPoint;

class CFGExprEvaluator
{
public:
	CFGExprEvaluator(CFG& cfg) : m_cfg(cfg){}

	void Evaluate();

private:

	CFG& m_cfg;
};
