#pragma once

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_matrix.hpp"
#include <fstream>
#include "GeneralMacros.h"
#include "boost/shared_ptr.hpp"
#include "FlowPoint.h"
#include "CommonGraphDefs.h"
#include "UniqueObjectIdMgr.h"

class MCGraph
	: public MCBaseGraph
{
	//friends
	friend InvariantMember make_invariant(const MCBaseGraph::edge_descriptor& e,const MCGraph& g);
public:

	MCGraph(unsigned int n = 0)
		: MCBaseGraph(n,getFriendlyName())
		, m_name(UniqueObjectIdMgr::NewMCId())
	{}

	MCGraph(const MCGraph& other)
		: MCBaseGraph(other)
		, m_name(UniqueObjectIdMgr::NewMCId())
	{
		//boost::put(boost::graph_name,*this,getFriendlyName());
		copyFrom(other);
	}

	friend std::ostream& operator <<(std::ostream& out,const MCGraph& mc);

	void setFlowPoints(FPSharedPtr from,FPSharedPtr to)
	{
		m_fromFlowPoint = from;
		m_toFlowPoint = to;
	}

	void addVar(const ParamName& var);
	void addVariables(const ParamNameSet& vars);


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
	void writeInArielFormat(std::ostream& out);

	//operators
	const MCGraph& operator=(const MCGraph& other);

protected:
	typedef std::map<std::string,vertex_descriptor> ParamNameToVertex;
	typedef std::set<vertex_descriptor> FlowPointParams;

	Invariant computeFlowPointInvariant(const FlowPointParams& fParams);
	void addInvariantFromFlowPoint(FPointWeakPtr fID);
	MCGraph::vertex_descriptor addVertexForVar(const ParamName& varName);
	
	ParamNameToVertex m_nameToVertex;
	FlowPointParams m_fromParams;
	FlowPointParams m_toParams;
	FPointWeakPtr m_fromFlowPoint;
	FPointWeakPtr m_toFlowPoint;
	unsigned int m_name;
	
private:
	//clones everything besides the name.
	void copyFrom(const MCGraph& other);
	void writeParamsInArielFormat(std::ostream& out,const FlowPointParams &fpParams);
};

typedef boost::shared_ptr<MCGraph> MCSharedPtr;

inline
std::string StringToWString(const std::string& s)
{
	std::string temp(s.length(),L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp; 
}