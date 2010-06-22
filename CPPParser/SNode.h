#pragma once
#include <vector>
#include "SyntaxParserInterface.h"

class SNode
{
public:
	SNode(nodeType type);
	SNode(const Node& node);
	virtual ~SNode(void);
	nodeType Type() {
		return m_Type;
	}

	const std::vector<SNode*>& children() {
		return m_chidren;
	}

private:
	nodeType m_Type;
	std::vector<SNode*> m_chidren;
};
