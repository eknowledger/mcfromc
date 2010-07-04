#include "Block.h"
#include <algorithm>

Block::Block(const std::string& name, FlowPoint* _parent) : 
FlowPoint(NULL, name), m_parent(_parent)
{
}

Block::~Block(void)
{
}

FlowPoint* Block::first()
{
	FlowPoint* fp = NULL;
	if (!m_flowPoints.empty()) {
		fp = m_flowPoints[0];
	}

	return fp;
}

FlowPoint* Block::last()
{
	FlowPoint* fp = NULL;
	if (!m_flowPoints.empty()) {
		fp = m_flowPoints[m_flowPoints.size()-1];
	}

	return fp;
}

FlowPoint* Block::parent() 
{
	return m_parent;
}


void Block::Add(FlowPoint* fp) 
{
	m_flowPoints.push_back(fp);
}

void Block::Remove(FlowPoint* fp) 
{
	std::vector<FlowPoint*>::iterator it = 
		std::find(m_flowPoints.begin(), m_flowPoints.end(), fp);
	if (it != m_flowPoints.end()) {
		m_flowPoints.erase(it);
	}
}