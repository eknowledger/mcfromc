#include "CFG.h"
#include <algorithm>
#include "SNode.h"
#include "Block.h"
#include "boost\graph\graphviz.hpp"

CFG::CFG(void)
{
}



CFG::~CFG(void)
{
	//struct VertexDelete
	//{
	//	void operator()(Vertex& v) {
	//		delete v.first;
	//	}
	//};

	//std::for_each(m_AdjList.begin(), m_AdjList.end(), VertexDelete());
}

FlowPoint* CFG::AddFlowPoint(SNode* node, std::string name)
{
	FlowPoint* fp = AddFlowPoint(new FlowPoint(node, name));
	boost::put(boost::vertex_name,*this,m_fpToV[fp],name);
	return fp;
}

FlowPoint* CFG::AddFlowPoint(FlowPoint* fp)
{
	FPSharedPtr spFP(fp);
	m_knownFPs.insert(spFP);
	CFGBase::vertex_descriptor v = boost::add_vertex(*this);
	m_fpToV[spFP.get()] = v;
	boost::put(boost::vertex_attachedFP,*this,v,FPointWeakPtr(spFP));
	return spFP.get();
}



void CFG::RemoveFlowPoint(FlowPoint* fp)
{
	CFGBase::vertex_descriptor v = m_fpToV[fp];
	boost::clear_vertex(v,*this);
	boost::remove_vertex(v,*this);
	FPSet::iterator itr = m_knownFPs.find(FPSharedPtr(fp));
	if(itr != m_knownFPs.end())
		m_knownFPs.erase(itr);
	FPToVertex::iterator itr2 = m_fpToV.find(fp);
	if(itr2 != m_fpToV.end())
		m_fpToV.erase(itr2);
}

void CFG::AddEdge(FlowPoint* f,FlowPoint* g)
{
	if (!isEdge(f,g)) {
		CFGBase::vertex_descriptor u = m_fpToV[f];
		CFGBase::vertex_descriptor v = m_fpToV[g];
		boost::add_edge(u,v,*this);
	}
}

void CFG::RemoveEdge(FlowPoint* f,FlowPoint* g)
{

	CFGBase::vertex_descriptor u = m_fpToV[f];
	CFGBase::vertex_descriptor v = m_fpToV[g];
	boost::remove_edge(u,v,*this);
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

FlowPointList CFG::neighbors(FlowPoint* fp)
{
	//std::list<Vertex>::iterator fpIt = findFlowPoint(fp);
	//if (fpIt != m_AdjList.end())
	//	return (*fpIt).second;
	//else
	//	return FlowPointList();
	FlowPointList retNeighbors;
	CFGBase::vertex_descriptor fpV = m_fpToV[fp];
	CFGBase::adjacency_iterator adjItr,adjEnd;
	for(boost::tie(adjItr,adjEnd) = boost::adjacent_vertices(fpV,*this); adjItr != adjEnd; ++adjItr){
		FPointWeakPtr attachedFP = boost::get(boost::vertex_attachedFP,*this,*adjItr);
		FPSharedPtr adjFP = attachedFP.lock();
		retNeighbors.push_back(adjFP.get());
	}
	return retNeighbors;
}

std::vector<FlowPoint*> CFG::flowPoints()
{
	std::vector<FlowPoint*> fps;
	for(FPSet::iterator fpItr = m_knownFPs.begin();fpItr != m_knownFPs.end(); ++fpItr){
		fps.push_back((*fpItr).get());
	}

	return fps;
}

bool CFG::isEdge(FlowPoint* f,FlowPoint *g)
{
	CFGBase::vertex_descriptor u = m_fpToV[f];
	CFGBase::vertex_descriptor v = m_fpToV[g];
	
	//pair <descriptor,exists>
	return boost::edge(u,v,*this).second;
}

void CFG::printForDot()
{
	printForDot(std::cout);
}

void CFG::printForDot(std::ostream& ostr)
{
	boost::write_graphviz(ostr,*this);
}