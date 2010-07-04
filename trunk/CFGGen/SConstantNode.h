#pragma once
#include "snode.h"

class SConstantNode : public SNode
{
public:
	SConstantNode(const NodeData& node): 
	  SNode(node), 
	  m_Value(node.m_constVal)
	{
	}

	virtual ~SConstantNode(void);

	int value() const {
		return m_Value;
	}

protected:
	virtual void printInfo(std::ostream&) const;

private:
	int m_Value;
};

