#include "SyntaxSimplifier.h"
#include "SNode.h"

SyntaxSimplifier::SyntaxSimplifier(SNode* root) : m_root(root)
{
}

SyntaxSimplifier::~SyntaxSimplifier(void)
{
}

void SyntaxSimplifier::execute()
{
	reduceChildren(m_root);
}

void SyntaxSimplifier::reduceChildren(SNode* node)
{
	std::vector<SNode*> children = node->children();
	size_t nChilds = children.size();
	for (size_t i = 0; i < nChilds; ++i) {
		reduceChildren(children[i]);
	}

	if (node->parent() && node->ShouldBeReduced()) {
		std::vector<SNode*>::iterator it = node->parent()->childIter(node);
		node->parent()->AddChildren(it, node->children().begin(), node->children().end());
		for (size_t i = 0; i < node->children().size(); ++i) {
			node->children()[i]->SetParent(node->parent());
		}
		node->parent()->RemoveChild(node);
		node->children().clear();
		delete node;
	}
}


