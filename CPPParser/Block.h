#pragma once
#include "flowpoint.h"
#include <vector>
#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////
/// This class represents a flow point which contains an ordered set of 
/// other flow points or blocks.
//////////////////////////////////////////////////////////////////////////
class Block : public FlowPoint
{
public:
	Block(const std::string& name, FlowPoint* _parent);
	virtual ~Block(void);
	void Add(FlowPoint* fp);
	void Remove(FlowPoint* fp);
	FlowPoint* first();
	FlowPoint* last();
	FlowPoint* parent();
	const std::vector<FlowPoint*>& flowPoints() const {
		return m_flowPoints;
	}

protected:
	Block(SNode* statement, const std::string& name, FlowPoint* _parent) : 
		 FlowPoint(statement, name), m_parent(_parent)
		 {
		 }
	std::vector<FlowPoint*> m_flowPoints;
	FlowPoint* m_parent;
};
