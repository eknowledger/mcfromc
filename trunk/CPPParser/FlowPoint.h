#pragma once

#include <string>

class SNode;

class FlowPoint
{
public:
	enum FlowPointType {
		FLOW_POINT,
		EXPRESSION_BLOCK
	};
	FlowPoint(void);
	FlowPoint(SNode* _node, std::string _name): 
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

	SNode* syntaxNode() {
		return m_node;
	}
private:
	int m_index;
	SNode* m_node;
	std::string m_name;
};
