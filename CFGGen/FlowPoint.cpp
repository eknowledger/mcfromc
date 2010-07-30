#include "FlowPoint.h"
#include "UniqueObjectIdMgr.h"

FlowPoint::FlowPoint(void)
{
}

FlowPoint::FlowPoint( SNode* _node, const std::string& _name ) : 
m_name(_name),
m_node(_node)
{
	m_index = UniqueObjectIdMgr::NewFlowPointId();
}
FlowPoint::~FlowPoint(void)
{
}
