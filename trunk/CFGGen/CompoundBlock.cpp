#include "CompoundBlock.h"
#include "ExpressionBlock.h"
#include "SyntaxUtils.h"

CompoundBlock::CompoundBlock(SNode* statement, FlowPoint* parent) :
Block(statement, "Compound_Block", parent)
{
}

CompoundBlock::~CompoundBlock()
{
}

std::vector<FlowPoint*> CompoundBlock::ReduceExpressionsToBlocks()
{
	std::vector<FlowPoint*> flowPoints;
	std::vector<FlowPoint*> newBlocks;
	for (size_t i = 0; i < m_flowPoints.size(); ++i) {
		if (SyntaxUtils::isExpression(m_flowPoints[i]->syntaxNode())) {
			size_t j = i;
			while (++j < m_flowPoints.size() &&
				   SyntaxUtils::isExpression(m_flowPoints[j]->syntaxNode()));

			ExpressionBlock* eb = new ExpressionBlock(NULL, parent());
			for (size_t k = i; k < j; ++k) {
				eb->Add(m_flowPoints[k]);
			}
			flowPoints.push_back(eb);
			newBlocks.push_back(eb);
			i = j-1;
		}
		else {
			flowPoints.push_back(m_flowPoints[i]);
		}
	}

	m_flowPoints = flowPoints;

	return newBlocks;
}
