#include "SNode.h"
#include "SyntaxNodeFactory.h"
#include <algorithm>

SNode::SNode(nodeType type) : 
	m_Type(type), 
	m_Parent(NULL)
{
}

SNode::SNode(const NodeData& node) : 
	m_Type(node.m_type), 
	m_Parent(NULL)
{
	m_children.reserve(node.m_childCount);
	for (size_t i = 0; i < node.m_childCount; ++i) {
		SNode* sn = SyntaxNodeFactory::the().createNode(node.m_childs[i]);
		sn->SetParent(this);
		m_children.push_back(sn);
	}

}

SNode::~SNode(void)
{
	for (size_t i = 0; i < m_children.size(); ++i) {
		delete m_children[i];
	}
}

void SNode::AddChild(SNode* newChild) 
{
	m_children.push_back(newChild);
}

void SNode::AddChildren(SNodeIterator& where, SNodeIterator& begin, SNodeIterator& end)
{
	m_children.insert(where, begin, end);
}


void SNode::RemoveChild(SNode* child) 
{
	std::vector<SNode*>::iterator it = 
		std::find(m_children.begin(), m_children.end(), child);
	if (it != m_children.end()) {
		m_children.erase(it);
	}
}

std::vector<SNode*>::iterator SNode::childIter(SNode* child)
{
	return std::find(m_children.begin(), m_children.end(), child);
}


void SNode::print(std::ostream& ostr, size_t level) const
{
	printType(ostr);
	printInfo(ostr);

	ostr << ("\n");

	//go over the children 
	size_t nChilds = m_children.size();
	for(size_t i = 0; i < nChilds; i++) {
		if (m_Parent)  {
			for(size_t j = 0; j < level+1; j++) {
				if (j == level)
				{
					ostr << ("|---");
				}
				else
				{
					ostr << ("    ");
				}
			}
		}
		m_children[i]->print(ostr, level+1);
	}
}

void SNode::printType(std::ostream& ostr) const
{
	switch(m_Type)
	{
	case STATEMENT: 
		ostr << "STATEMENT ";
		break;
	case STATEMENT_LIST: ostr << "STATEMENT_LIST ";
		break;
	case CONDITION_IF: ostr << "IF ";
		break;
	case CONDITION_IF_ELSE: ostr << "IF_ELSE ";
		break;
	case EXPRESSION: ostr << "EXPRESSION ";
		break;
	case CONDITIONAL_EXPRESSION: ostr << "CONDITIONAL_EXPRESSION ";
		break;
	case EXPRESSION_STATEMENT: ostr << "EXPRESSION_STATEMENT ";
		break;
	case ASSIGNMENT_EXPR: ostr << "ASSIGNMENT_EXPRESSION ";
		break;
	case BLOCK: ostr << "BLOCK ";
		break;
	case NONE: ostr << "NONE ";
		break;
	case ID: ostr << "IDENTIFIER ";
		break;
	case CONST_TYPE: 
		ostr << "CONSTANT ";
		break;
	case SELECTION_STATEMENT: ostr << "SELECTION_STATEMENT ";
		break;
	case ADD_EXPR: ostr << "ADD ";
		break;
	case SUB_EXPR: ostr << "SUBTRACT ";
		break;
	case MULT_EXPR: ostr << "MULTIPLY ";
		break;
	case DIV_EXPR: ostr << "DIV_EXPR ";
		break;
	case PRE_INCREMENT_UNARY_EXPR: ostr << "PRE_INCREMENT ";
		break;
	case PRE_DECREMENT_UNARY_EXPR: ostr << "PRE_DECREMENT ";
		break;
	case POST_INCREMENT_EXPR: ostr << "POST_INCREMENT ";
		break;
	case POST_DECREMENT_EXPR: ostr << "POST_DECREMENT ";
		break;
	case PREFIX_PLUS: ostr << "PREFIX_PLUS ";
		break;
	case PREFIX_MINUS: ostr << "PREFIX_MINUS ";
		break;
	case PREFIX_NOT: ostr << "PREFIX_NOT ";
		break;
	case LESS_THAN_EXPR: ostr << "LESS ";
		break;
	case GREATER_THAN_EXPR: ostr << "GREATER ";
		break;
	case LESS_EQ_THAN_EXPR: ostr << "LESS_OR_EQUAL ";
		break;
	case GREATER_EQ_THAN_EXPR: ostr << "GREATER_OR_EQUAL ";
		break;
	case DECLARATION: ostr << "DECLARATION ";
		break;
	case INIT_DECLARATOR_LIST: ostr << "INIT_DECLARATOR_LIST ";
		break;
	case TYPE_SPECIFIER: ostr << "TYPE_SPECIFIER ";
		break;
	case PARAM_LIST: ostr << "PARAM_LIST ";
		break;
	case PARAM_DECLARATION: ostr << "PARAM_DECLARATION ";
		break;
	case DECLARATION_LIST: ostr << "DECLARATION_LIST ";
		break;
	case TRANSLATION_UNIT: ostr << "TRANSLATION_UNIT ";
		break;
	case COMPOUND_STATEMENT: ostr << "COMPOUND_STATEMENT ";
		break;
	case WHILE_LOOP: ostr << "WHILE_LOOP ";
		break;
	case DO_WHILE_LOOP: ostr << "DO_WHILE_LOOP ";
		break;
	case FOR_LOOP: ostr << "FOR_LOOP ";
		break;
	default:
		ostr << "?? what ?? ";
		break;
	}
}
