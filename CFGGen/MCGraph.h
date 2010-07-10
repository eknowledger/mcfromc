#pragma once

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_matrix.hpp"
#include <fstream>
#include "GeneralMacros.h"
#include "boost/shared_ptr.hpp"
#include "FlowPoint.h"
#include "CommonGraphDefs.h"

class MCGraph
	: public MCBaseGraph
{
	//friends
	friend InvariantMember make_invariant(const MCBaseGraph::edge_descriptor& e,const MCGraph& g);
public:

	MCGraph(unsigned int n = 0)
		: MCBaseGraph(n,getFriendlyName())
		, m_name(++McNum)
	{}

	MCGraph(const MCGraph& other)
		: MCBaseGraph(other)
		, m_name(++McNum)
	{
		//boost::put(boost::graph_name,*this,getFriendlyName());
		copyFrom(other);
	}

	friend std::wostream& operator <<(std::wostream& out,const MCGraph& mc);

	void setFlowPoints(FPSharedPtr from,FPSharedPtr to)
	{
		m_fromFlowPoint = from;
		m_toFlowPoint = to;
	}

	Invariant computeInvariant(const FlowPoint& f);
	std::string getFriendlyName() const{
		std::stringstream friendlyName;
		friendlyName << "G" << m_name;
		return friendlyName.str();
	}
	bool logicalClosure();
	edge_descriptor addOrUpdateEdge(vertex_descriptor u,vertex_descriptor v,Order o);
	MCConstrainEdge addEdgeFromInvariant(const InvariantMember& inv);
	void removeEdgeFromInvariant(const InvariantMember& inv);

	//operators
	const MCGraph& operator=(const MCGraph& other);

protected:
	typedef std::map<vertex_descriptor,std::wstring> VertexToParamName;
	typedef std::map<std::wstring,vertex_descriptor> ParamNameToVertex;
	typedef std::set<vertex_descriptor> FlowPointParams;

	Invariant computeFlowPointInvariant(const FlowPointParams& fParams);
	void addInvariantFromFlowPoint(FPointWeakPtr fID);
	
	VertexToParamName m_paramVertexToName;
	ParamNameToVertex m_nameToVertex;
	FlowPointParams m_fromParams;
	FlowPointParams m_toParams;
	FPointWeakPtr m_fromFlowPoint;
	FPointWeakPtr m_toFlowPoint;
	unsigned int m_name;
	
private:
	//clones everything besides the name.
	void copyFrom(const MCGraph& other);
	static unsigned int McNum;
};

typedef boost::shared_ptr<MCGraph> MCSharedPtr;
