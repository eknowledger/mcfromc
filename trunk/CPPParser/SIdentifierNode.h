#pragma once
#include "snode.h"

class SIdentifierNode : public SNode
{
public:
	SIdentifierNode(const NodeData& node): 
	  SNode(node), 
	  m_Name(node.m_name)
	{
	}

	virtual ~SIdentifierNode(void);

	const std::string& name() const {
		return m_Name;
	}

protected:
	virtual void printInfo(std::ostream& ostr) const 
	{
		ostr << m_Name;
	}

private:
	std::string m_Name;
};
