#include "CFG.h"
#include <algorithm>
#include "SNode.h"
#include "Block.h"

CFG::CFG(void)
{
}



CFG::~CFG(void)
{
	struct VertexDelete
	{
		void operator()(Vertex& v) {
			delete v.first;
		}
	};

	std::for_each(m_AdjList.begin(), m_AdjList.end(), VertexDelete());
}

FlowPoint* CFG::AddFlowPoint(SNode* node, std::string name)
{
	FlowPoint* fp = new FlowPoint(node, name);
	m_AdjList.push_back(Vertex(fp));
	return fp;
}


FlowPoint* CFG::RemoveFlowPoint(FlowPoint* fp)
{
	FlowPoint* fpOut = NULL;

	std::list<Vertex>::iterator it = findFlowPoint(fp);
	if (it != m_AdjList.end()) {
		fpOut = (*it).first;
		m_AdjList.erase(it);
	}

	return fpOut;
}

void CFG::AddEdge(Edge e)
{
	std::list<Vertex>::iterator adjIt = findFlowPoint(e.first);
	if (adjIt != m_AdjList.end()) {
		FlowPointIterator fpIt = findFlowPoint(adjIt, e.second);
		if (fpIt == (*adjIt).second.end()) {
			(*adjIt).second.push_back(e.second);
		}
	}
}

void CFG::RemoveEdge(Edge edge)
{
	std::list<Vertex>::iterator adjIt = findFlowPoint(edge.first);
	if (adjIt != m_AdjList.end()) {
		FlowPointIterator fpIt = findFlowPoint(adjIt, edge.second);
		if (fpIt != (*adjIt).second.end()) {
			(*adjIt).second.erase(fpIt);
		}
	}
}

std::list<CFG::Vertex>::iterator CFG::findFlowPoint( FlowPoint* fp )
{
	struct IsSameFlowPoint {
		IsSameFlowPoint(const FlowPoint* _fp) : m_fp(_fp) {		
		}

		bool operator()(const FlowPointAndNeighbors& fpn) const {
			return m_fp == fpn.first;
		}

		const FlowPoint* m_fp;
	};

	std::list<CFG::Vertex>::iterator it = std::find_if(m_AdjList.begin(), m_AdjList.end(), IsSameFlowPoint(fp));
	return it;

}

FlowPointIterator CFG::findFlowPoint(const std::list<CFG::Vertex>::iterator& it, const FlowPoint* fp)
{
	FlowPointList& fpList = (*it).second;
	FlowPointIterator fpIt = std::find(fpList.begin(), fpList.end(), fp);

	return fpIt;
}

void CFG::print()
{
	std::list<CFG::Vertex>::iterator it;
	for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it) {
		if ((*it).first->syntaxNode()->Type() == ASSIGNMENT_EXPR ||
			(*it).first->syntaxNode()->Type() == POST_INCREMENT_EXPR ||
			(*it).first->syntaxNode()->Type() == POST_DECREMENT_EXPR) {
			continue;
		}

		std::cout << std::endl << (*it).first->index() << " " 
			<< (*it).first->name() << " : Edges to: ";
		for (FlowPointIterator fpIt = (*it).second.begin(); fpIt != (*it).second.end(); ++fpIt) {
			std::cout << (*fpIt)->index() << ", ";
		}
		std::cout << std::endl << *((*it).first->syntaxNode());
		
	}
}

Block* CFG::AddBlock(SNode* statement, std::string name )
{
	Block* block = new Block(statement, name);
	m_AdjList.push_back(Vertex(block));
	return block;
}

FlowPointList CFG::neighbors(FlowPoint* fp)
{
	std::list<Vertex>::iterator fpIt = findFlowPoint(fp);
	if (fpIt != m_AdjList.end())
		return (*fpIt).second;
	else
		return FlowPointList();
}

bool CFG::isEdge( Edge e )
{
	bool rc = false;
	std::list<Vertex>::iterator adjIt = findFlowPoint(e.first);
	if (adjIt != m_AdjList.end()) {
		FlowPointIterator fpIt = findFlowPoint(adjIt, e.second);
		if (fpIt != (*adjIt).second.end()) {
			rc = true;
		}
	}

	return rc;
}