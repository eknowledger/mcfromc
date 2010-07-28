#include "CFG.h"
#include <algorithm>
#include "SNode.h"
#include "Block.h"
#include "boost\graph\graphviz.hpp"
#include "GeneralMacros.h"
#include "boost/make_shared.hpp"

CFG::CFG(void): m_startFP(NULL)
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
	for(FPSet::iterator fpItr = m_knownFPs.begin(); fpItr != m_knownFPs.end(); ++fpItr)
	{
		if ((*fpItr).get() == fp)
		{
			m_knownFPs.erase(fpItr);
			break;
		}
	}

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

namespace{
	//this should be removed because we need to move to FPSharedPTR in all 
	//places
	FPSharedPtr findKnownShared(FPSet& fps,FlowPoint* f)
	{
		for(FPSet::iterator fItr = fps.begin(); fItr != fps.end(); ++fItr){
			if(fItr->get() == f)
				return *fItr;
		}
		return FPSharedPtr();
	}
}

MCSharedPtr CFG::AddEdge(FlowPoint* f,FlowPoint* g)
{
	CFGBase::vertex_descriptor u = f->cfgID();
	CFGBase::vertex_descriptor v = g->cfgID();
	CFGBase::edge_descriptor e = boost::add_edge(u,v,*this).first;

	//creates the MC that is attached to the C.F.G
	MCSharedPtr spMC(new MCGraph());
	FPSharedPtr spF = findKnownShared(m_knownFPs,f);
	FPSharedPtr spG = findKnownShared(m_knownFPs,g);
	ASSERT_RETURN(spF != NULL && spG != NULL,MCSharedPtr());
	spMC->setFlowPoints(spF,spG);
	boost::put(boost::edge_sizeChange,*this,e,MCWeakPtr(spMC));
	m_knwonMCs.insert(spMC);

	return spMC;
}

void CFG::RemoveEdge(FlowPoint* f,FlowPoint* g)
{

	CFGBase::vertex_descriptor u = f->cfgID();
	CFGBase::vertex_descriptor v = g->cfgID();
	
	//removes the mc from the known MCs
	CFGBase::edge_descriptor e = boost::edge(u,v,*this).first;
	MCWeakPtr attachedMC = boost::get(boost::edge_sizeChange,*this,e);
	MCSharedPtr spMC = attachedMC.lock();
	MCSet::iterator mcItr = m_knwonMCs.find(spMC);
	if(mcItr != m_knwonMCs.end())
		m_knwonMCs.erase(mcItr);

	boost::remove_edge(u,v,*this);
}

FlowPointList CFG::neighbors(FlowPoint* fp)
{
	FlowPointList retNeighbors;
	FP_CFG_ID fpV = fp->cfgID();
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

	return fps;
}

bool CFG::isEdge(FlowPoint* f,FlowPoint *g)
{
	CFGBase::vertex_descriptor u = f->cfgID();
	CFGBase::vertex_descriptor v = g->cfgID();
	
	//pair <descriptor,exists>
	return boost::edge(u,v,*this).second;
}

/// Returns all Flow Points s.t. there is an edge from them to fp.
FlowPointList CFG::ancestors(FlowPoint* fp)
{
	FlowPointList preds;
	FP_CFG_ID fpV = fp->cfgID();
	CFGBase::in_edge_iterator e, e_end;
	for (tie(e, e_end) =  boost::in_edges(fpV, *this); e != e_end; ++e)
	{
		FPointWeakPtr attachedFP = boost::get(boost::vertex_attachedFP,
											  *this,
											  boost::source(*e,*this));
		FPSharedPtr adjFP(attachedFP.lock());
		preds.push_back(adjFP.get());
	}

	return preds;
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

struct EdgeMCPropertyWriter {
	EdgeMCPropertyWriter(CFG &g_) : g(g_) {}
	template <class MyEdge>
	void operator() (std::ostream &out, MyEdge e) {
		MCWeakPtr attachedMC = boost::get(boost::edge_sizeChange,g,e);
		MCSharedPtr spMC = attachedMC.lock();		
		std::string name = spMC->getFriendlyName();
		out << "[label=" << name << "]";
	}

	CFG &g;
};
void CFG::printForDot(std::ostream& ostr)
{
	boost::write_graphviz(ostr,*this, VertexFlowPointPropertyWriter(*this),EdgeMCPropertyWriter(*this));
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

void CFG::SetStart( FlowPoint* startFP )
{
	m_startFP = startFP;
}

FlowPoint* CFG::Start() const
{
	return m_startFP;
}

const ParamNameSet& CFG::Variables() const
{
	return m_knownVariables;
}

void CFG::AddVariable( const ParamName& varName )
{
	m_knownVariables.insert(varName);
}

const MCSet& CFG::KnownMCs() const
{
	return m_knwonMCs;
}