#pragma once

#include "CFG.h"
#include "ExprMgr.h"
#include <boost/graph/depth_first_search.hpp>
#include <vector>
#include "CommonGraphDefs.h"

class FlowPoint;
typedef std::map<FP_CFG_ID,VarToValue> FPIDToVarState;

class CFGExprEvaluator
{
public:
	CFGExprEvaluator(CFG& cfg) : m_cfg(cfg){}

	void Evaluate();

protected:
	void updateMCsWithTransitionsVariants(FPIDToVarState& fpStates);
	TransitionVariantSet ComputeExprBlockInvariants(VarToValue& inValue, VarToValue& outValue) const;

private:

	CFG& m_cfg;
};
