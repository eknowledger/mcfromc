#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SyntaxParserInterface.h"

class SNode
{
public:
	SNode(nodeType type);
	SNode(const NodeData& node);
	virtual ~SNode(void);
	nodeType Type() {
		return m_Type;
	}

	const std::vector<SNode*>& children() {
		return m_chidren;
	}

	SNode* parent() {
		return m_Parent;
	}

	void SetParent(SNode* newParent) {
		m_Parent = newParent;
	}

protected:
	friend std::ostream& operator<<(std::ostream& os,const SNode& node);
	
	void print(std::ostream& ostr, size_t level) const;
	void printType(std::ostream& ostr) const;
	virtual void printInfo(std::ostream& ostr) const;

private:
	nodeType m_Type;
	SNode* m_Parent;
	std::vector<SNode*> m_chidren;
};

inline
std::ostream& operator<<(std::ostream& os,const SNode& node)
{
	node.print(os,0);
	return os;
}

inline 
void SNode::printInfo(std::ostream&) const {
}