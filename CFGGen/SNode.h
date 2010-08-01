#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SyntaxParserInterface.h"

class SNode;
typedef std::vector<SNode*>::iterator SNodeIterator;

class SNode
{
public:
	SNode(nodeType type);
	SNode(const NodeData& node);
	virtual ~SNode(void);
	nodeType Type() {
		return m_Type;
	}

	std::vector<SNode*>& children() {
		return m_children;
	}

	SNode* parent() {
		return m_Parent;
	}

	void SetParent(SNode* newParent) {
		m_Parent = newParent;
	}

	SNodeIterator childIter(SNode* child);

	void AddChild(SNode* newChild);
	void AddChildren(SNodeIterator& where, SNodeIterator& begin, SNodeIterator& end);

	void RemoveChild(SNode* child);

	virtual bool ShouldBeReduced() {
		return false;
	}

	virtual bool ShouldCreateEdgeFromChildren() {
		return false;
	}

	int codeRow() const {
		return m_row;
	}

	int codeColumn() const {
		return m_column;
	}

	virtual bool IsOrderCondition() const {
		return false;
	}

	std::string Text() const;

	virtual bool IsValidExpression() {
		return true;
	}

protected:
	friend std::ostream& operator<<(std::ostream& os,const SNode& node);
	
	void print(std::ostream& ostr, size_t level) const;
	void printType(std::ostream& ostr) const;
	virtual void printInfo(std::ostream& ostr) const;

private:
	int m_row;
	int m_column;
	nodeType m_Type;
	SNode* m_Parent;
	std::vector<SNode*> m_children;
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