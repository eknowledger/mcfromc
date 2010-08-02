#include "FlowPoint.h"
#include "UniqueObjectIdMgr.h"
#include "SyntaxUtils.h"

FlowPoint::FlowPoint(void)
{
	m_index = -1;
	m_node = NULL;
}

FlowPoint::FlowPoint( SNode* _node, const std::string& _name ) : 
m_name(_name),
m_node(_node)
{
	m_index = -1;
}
FlowPoint::~FlowPoint(void)
{
}

bool FlowPoint::ShouldBeAssignedId()
{
	return Type() == EXPRESSION_BLOCK ||
		(m_node &&
		(SyntaxUtils::isBranch(m_node) ||
		SyntaxUtils::isLoop(m_node)));
}

void FlowPoint::AssignUniqueId()
{
	m_index = UniqueObjectIdMgr::NewFlowPointId();
}