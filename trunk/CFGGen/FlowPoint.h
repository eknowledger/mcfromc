#pragma once

#include <string>
#include "CommonGraphDefs.h"
#include "expr.h"

class SNode;

//////////////////////////////////////////////////////////////////////////
/// Basic class representing a flow point in a Control Flow Graph.
//////////////////////////////////////////////////////////////////////////
class FlowPoint
{
public:
	enum FlowPointType {
		FLOW_POINT,
		EXPRESSION_BLOCK,
		COMPOUND_BLOCK,
		FOR_LOOP_FLOW_POINT
	};
	FlowPoint(void);
	FlowPoint(SNode* _node, const std::string& _name);

	virtual FlowPointType Type() {
		return FLOW_POINT;
	}

	virtual ~FlowPoint(void);

	const std::string& name() const {
		return m_name;
	}

	int index() const {
		return m_index;
	}

	void AssignUniqueId();

	bool ShouldBeAssignedId();

	inline FP_CFG_ID cfgID() const {
		return m_cfgID;
	}

	inline void setCfgID(FP_CFG_ID newID){
		m_cfgID = newID;
	}

	SNode* syntaxNode() {
		return m_node;
	}

	std::string getFriendlyName() const
	{
		std::ostringstream ostr;
		ostr << "f" << m_index;
		return ostr.str();
	}

	//VarToValue& InValue() {
	//	return m_inValue;
	//}

	//VarToValue& OutValue() {
	//	return m_outValue;
	//}

	//Invariant& SizeChange() {
	//	return m_sizeChangeInv;
	//}

private:
	int m_index;
	FP_CFG_ID m_cfgID;
	SNode* m_node;
	std::string m_name;

	//The following members are for test purposes and thus are commented out:
	//VarToValue m_inValue;
	//VarToValue m_outValue;
	//Invariant m_sizeChangeInv;
};
