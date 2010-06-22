#include "SNode.h"

SNode::SNode(nodeType type) : m_Type(type)
{
}

SNode::SNode(const Node& node) : m_Type(node.m_type)
{
	m_chidren.reserve(node.m_childCount);
	for (size_t i = 0; i < node.m_childCount; ++i) {
		m_chidren.push_back(new SNode(*(node.m_childs[i])));
	}
}

SNode::~SNode(void)
{
	for (size_t i = 0; i < m_chidren.size(); ++i) {
		delete m_chidren[i];
	}
}
