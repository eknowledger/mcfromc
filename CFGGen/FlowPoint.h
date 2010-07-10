#pragma once

#include <string>
#include "CommonGraphDefs.h"

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
		COMPOUND_BLOCK
	};
	FlowPoint(void);
	FlowPoint(SNode* _node, const std::string& _name): 
		m_name(_name),
		m_node(_node)
	{
		static int globalIndex = 0;
		m_index = globalIndex;
		globalIndex++;
	}

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

	FP_CFG_ID cfgID() const {
		return m_cfgID;
	}

	SNode* syntaxNode() {
		return m_node;
	}
private:
	int m_index;
	FP_CFG_ID m_cfgID;
	SNode* m_node;
	std::string m_name;
};
