#include "CFG.h"
#include <algorithm>
#include "SNode.h"
#include "Block.h"
#include "boost\graph\graphviz.hpp"
#include "GeneralMacros.h"

CFG::CFG(void)
{
}

FlowPoint* CFG::AddFlowPoint(SNode* node, std::string name)
{
	FlowPoint* fp = AddFlowPoint(new FlowPoint(node, name));
	boost::put(boost::vertex_name,*this,fp->cfgID(),name);
	return fp;
}

FlowPoint* CFG::AddFlowPoint(FlowPoint* fp)
{
	FPSharedPtr spFP(fp);
	m_knownFPs.insert(spFP);
	CFGBase::vertex_descriptor v = boost::add_vertex(*this);
	spFP->setCfgID(v);
	boost::put(boost::vertex_attachedFP,*this,v,FPointWeakPtr(spFP));
	return spFP.get();
}



void CFG::RemoveFlowPoint(FlowPoint* fp)
{
	CFGBase::vertex_descriptor v = fp->cfgID();
	boost::clear_vertex(v,*this);
	boost::remove_vertex(v,*this);

	//remove gets the FP from the set
	FPSet::iterator fpItr = m_knownFPs.find(FPSharedPtr(fp));
	if(fpItr != m_knownFPs.end())
		m_knownFPs.erase(fpItr);

	//repopulate flow point to vertex descriptor map.
	CFGBase::vertex_iterator adjItr,adjEnd;
	for(boost::tie(adjItr,adjEnd) = boost::vertices(*this); adjItr != adjEnd; ++adjItr){
		CFGBase::vertex_descriptor fpV = (*adjItr);
		FPointWeakPtr attachedFP = boost::get(boost::vertex_attachedFP,*this,*adjItr);
		FPSharedPtr adjFP(attachedFP.lock());
		ASSERT_LOOP_CONTINUE(adjFP != NULL);
		adjFP->setCfgID(fpV);
	}
}

void CFG::AddEdge(FlowPoint* f,FlowPoint* g)
{
	CFGBase::vertex_descriptor u = f->cfgID();
	CFGBase::vertex_descriptor v = g->cfgID();
	boost::add_edge(u,v,*this);
}

void CFG::RemoveEdge(FlowPoint* f,FlowPoint* g)
{

	CFGBase::vertex_descriptor u = f->cfgID();
	CFGBase::vertex_descriptor v = g->cfgID();
	boost::remove_edge(u,v,*this);
}

FlowPointList CFG::neighbors(FlowPoint* fp)
{
	FlowPointList retNeighbors;
	CFGBase::vertex_descriptor fpV = fp->cfgID();
	CFGBase::adjacency_iterator adjItr,adjEnd;
	for(boost::tie(adjItr,adjEnd) = boost::adjacent_vertices(fpV,*this); adjItr != adjEnd; ++adjItr){
		FPointWeakPtr attachedFP = boost::get(boost::vertex_attachedFP,*this,*adjItr);
		FPSharedPtr adjFP(attachedFP.lock());
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

	for(FPSet::iterator fpItr = m_hiddenFPs.begin();fpItr != m_hiddenFPs.end(); ++fpItr){
		fps.push_back((*fpItr).get());
	}

	return fps;
}

bool CFG::isEdge(FlowPoint* f,FlowPoint *g)
{
	CFGBase::vertex_descriptor u = f->cfgID();
	CFGBase::vertex_descriptor v = g->cfgID();
	
	//pair <descriptor,exists>
	return boost::edge(u,v,*this).second;
}

void CFG::printForDot()
{
	printForDot(std::cout);
}

struct VertexFlowPointPropertyWriter {
	VertexFlowPointPropertyWriter(CFG &g_) : g(g_) {}
	template <class MyVertex>
	void operator() (std::ostream &out, MyVertex u) {
		std::string name = boost::get(boost::vertex_attachedFP,g,u).lock().get()->name();
		out << "[label=" << name << "]";
	}

	CFG &g;
};

void CFG::printForDot(std::ostream& ostr)
{
	boost::write_graphviz(ostr,*this, VertexFlowPointPropertyWriter(*this));
}

FlowPoint* CFG::AddHiddenFlowPoint( SNode* node, std::string name )
{
	FlowPoint* fp = new FlowPoint(node, name);
	m_hiddenFPs.insert(FPSharedPtr(fp));
	return fp;
}

std::string CFG::getName( FlowPoint* fp )
{
	CFGBase::vertex_descriptor fpV = fp->cfgID();
	std::ostringstream ostr;
	ostr << fpV;

	return ostr.str();
}