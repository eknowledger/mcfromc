#define _SCL_SECURE_NO_WARNINGS

#include "MCGraph.h"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/floyd_warshall_shortest.hpp"
#include "boost/graph/depth_first_search.hpp"
#include "boost/multi_array.hpp"
#include "boost/graph/graphviz.hpp"

namespace{
	struct MCGraphWriter {
		MCGraphWriter(const MCGraph * const g)
			:m_g(g)
		{}

		void operator()(std::ostream& out) const {
			out << "label=" << 
				   m_g->getFriendlyName() << ";\n rankdir=LR;\n";
		}
		const MCGraph * const m_g;
	};
}

InvariantMember make_invariant(const MCBaseGraph::edge_descriptor& e,const MCGraph& g){
	MCBaseGraph::vertex_descriptor u,v; 

	//Gets the vertex that compose the edge
	u = boost::source(e,g);
	v = boost::target(e,g);
	//Gets the invariant parameters
	std::wstring x1Name,x2Name;
	Order o = END_ORDER;
	x1Name = boost::get(boost::vertex_name,g,u);
	x2Name = boost::get(boost::vertex_name,g,v);
	o = (Order) boost::get(boost::edge_weight,g,e);
	
	return boost::make_tuple(x2Name,o,x1Name);
}

MCConstrainEdge MCGraph::addEdgeFromInvariant(const InvariantMember& inv){
	//Gets the vertex that are associated with the param names
	MCGraph::ParamNameToVertex::const_iterator x = m_nameToVertex.find(inv.get<0>());
	MCGraph::ParamNameToVertex::const_iterator y = m_nameToVertex.find(inv.get<2>());
	MCBaseGraph::edge_descriptor invEdge;

	MCGraph::vertex_descriptor u, v;
	if (x != m_nameToVertex.end())
	{
		u = x->second;
	}
	else 
	{
		u = boost::add_vertex( *this);
		boost::put(boost::vertex_name,*this,u,inv.get<0>());
		m_nameToVertex[inv.get<0>()] = u;
	}
	
	if (y != m_nameToVertex.end())
	{
		v = y->second;
	}
	else 
	{
		v = boost::add_vertex(*this);
		boost::put(boost::vertex_name,*this,v,inv.get<2>());
		m_nameToVertex[inv.get<2>()] = v;
	}

	//Gets the order.
	Order o = inv.get<1>();
	ASSERT_RETURN(o != END_ORDER,invEdge);
	//we do y -> to x since x < y means there is an edge from y to x
	invEdge = addOrUpdateEdge(u, v, o);
	return invEdge;
}

void MCGraph::removeEdgeFromInvariant(const InvariantMember& inv)
{
	//Gets the vertex that are associated with the param names
	MCGraph::ParamNameToVertex::const_iterator x = m_nameToVertex.find(inv.get<0>());
	MCGraph::ParamNameToVertex::const_iterator y = m_nameToVertex.find(inv.get<2>());
	ASSERT_RETURN_VOID(x != m_nameToVertex.end() && y != m_nameToVertex.end());
	//remove the edge from the graph.
	boost::remove_edge(y->second,x->second,*this);

}

unsigned int MCGraph::McNum = 0;

Invariant MCGraph::computeInvariant(const FlowPoint& f)
{
	Invariant resFPInv;

	FPSharedPtr fromFP = m_fromFlowPoint.lock();
	FPSharedPtr toFP = m_toFlowPoint.lock();
	ASSERT_RETURN(fromFP != NULL && toFP != NULL,resFPInv);

	if(f.cfgID() == fromFP->cfgID())
		return computeFlowPointInvariant(m_fromParams);
	else if(f.cfgID() == toFP->cfgID())
		return computeFlowPointInvariant(m_toParams);
	else
		ASSERT_RETURN(!"Unknown MC Flowpoint",Invariant());

	return resFPInv;
}

Invariant MCGraph::computeFlowPointInvariant(const FlowPointParams& fParams)
{
	Invariant resInvariant;
	//The invariant are edges between the parameters of the flow point, instead
	//of between flowpoints.
	//so the algorithm is:
	//for each edge 
	//	if source and target are in same flow point 
	//		add it to invariant.
	edge_iterator edge = edges(*this).first;
	edge_iterator last = edges(*this).second;
	for(;edge != last ; ++edge)
	{
		FlowPointParams::const_iterator flowPointParamItr = fParams.find(source(*edge,*this));
		if(flowPointParamItr == fParams.end())
			continue;	//This is not invariant edge.
		flowPointParamItr = fParams.find(target(*edge,*this));
		if(flowPointParamItr == fParams.end())
			continue;	//This is not invariant edge.
		std::wstring srcName,trgName;
		//Gets the name of the parameterts and order to make Invariant Member.

		resInvariant.insert(make_invariant(*edge,*this));
	}
	return resInvariant;
}

namespace{
	template<typename Graph>
	struct MCEdgeWriter
	{
		MCEdgeWriter(const Graph& g)
			: m_g(g)
		{}

		template <typename Edge>
		void operator()(std::ostream& out, const Edge& e) const
		{
			Order o = END_ORDER;
			std::string color;
			o = (Order) boost::get(boost::edge_weight,m_g,e);
			switch(o)
			{
			case LEQ: 
				color = "black";
				break;
			case LESS:
				color = "red";
				break;
			default:
				_ASSERT(!"Arc with unknown weight");
			}
			out << "[color=\"" << color << "\"]";
		}

		const Graph& m_g;
	};

	template<typename Graph>
	struct MCVertexWriter
	{
		MCVertexWriter(const Graph& g)
			: m_g(g)
		{}

		template <typename Vertex>
		void operator()(std::ostream& out, const Vertex& v) const
		{
			std::wstring name = boost::get(boost::vertex_name,m_g,v);

			std::string str;
			str.assign(name.begin(), name.end());
			out << "[label=\"" << str << "\" fontsize=13 shape=plaintext]";
		}

		const Graph& m_g;
	};

}

std::wostream& operator <<(std::wostream& out,const MCGraph& mc)
{
	out << std::endl;
	std::stringstream sMC;
	boost::property_map<MCBaseGraph,boost::vertex_name_t>::const_type vNameProp = get(boost::vertex_name,mc);
	boost::write_graphviz(sMC,mc,MCVertexWriter<MCGraph>(mc),MCEdgeWriter<MCGraph>(mc),MCGraphWriter(&mc));
	out << sMC.str().c_str();
	out << std::endl;
	return out;
}

MCGraph::edge_descriptor MCGraph::addOrUpdateEdge(vertex_descriptor u,vertex_descriptor v,Order o)
{
	bool exists = false;
	vertex_descriptor source(u),target(v);
	
	//gets the real source and target of edge.
	switch(o){
		case LESS:
		case LEQ:
			break;
		//stays the same
		case GREATER:
			source = v;
			target = u;
			o = LESS;
			break;
		case GEQ:
			source = v;
			target = u;
			o = LEQ;
			break;			
	}

	edge_descriptor e;
	boost::tie(e,exists) = boost::edge(source,target,*this);
	if(exists){
		//checks if we need to update it.
		Order current = (Order) boost::get(boost::edge_weight,*this,e);
		if(current == LEQ && o == LESS)
			boost::put(boost::edge_weight,*this,e,o);
		return e;
	}
	else
		return add_edge(u,v,o,*this).first;
}

/*Algorithm:

	*) add arcs the represents flow point's invariant.
	*) put weight -1 for each strict arc and 0 for each regular arc.
	*) if G contains negative cycle return error.
	*) for each u,v do
		*) compute short path between u,v if there is no path continue to next pair.
		*) if the path is negative then add strict arc between u->v
		*) else add non strict arc u->v
	
*/
bool MCGraph::logicalClosure()
{
	//add edges that represents the invariants
	addInvariantFromFlowPoint(m_fromFlowPoint);
	addInvariantFromFlowPoint(m_toFlowPoint);

	typedef boost::multi_array<MCEdgeWeight,2> DistanceMatrix;
	DistanceMatrix d(boost::extents[num_vertices(*this)][num_vertices(*this)]);
	
	//we compute the shortest path between all pairs of vertices using 
	//floyd warshal, the algorithm returns false if there is negative cycle.
	bool success = boost::floyd_warshall_all_pairs_shortest_paths(*this,d,boost::distance_zero(0));
	if(!success){
		return false;
	}

	//go over all the pairs of vertices.
	vertex_iterator uItr,uEnd,vItr,vEnd;

	for(boost::tie(uItr,uEnd) = vertices(*this); uItr != uEnd; ++uItr)
		for(boost::tie(vItr,vEnd) = vertices(*this); vItr != vEnd; ++vItr)
		{
			if(*uItr == *vItr)
				//same vertex continue.
				continue;

			//what the distance between u,v?
			if(d[*uItr][*vItr] == LEQ)
				//the path is not strict, and there isn't an edge already
				addOrUpdateEdge(*uItr,*vItr,LEQ);
			else if (d[*uItr][*vItr] < 0){
				//the path is strict add a strict edge.
				addOrUpdateEdge(*uItr,*vItr,LESS);
			}
		}

	return true;
}

void MCGraph::addInvariantFromFlowPoint(FPointWeakPtr fWeak)
{
	FPSharedPtr spF = fWeak.lock();
	ASSERT_RETURN_VOID(spF != NULL);
	//Invariant& inv = f->getInvariant();
	Invariant inv;
	for(Invariant::iterator invItr = inv.begin(); invItr != inv.end(); ++invItr)
		addEdgeFromInvariant(*invItr);
	
}

void MCGraph::copyFrom(const MCGraph& other)
{
	*((MCBaseGraph*)this) = (MCBaseGraph) other;
	m_paramVertexToName = other.m_paramVertexToName;
	m_nameToVertex = other.m_nameToVertex;
	m_fromParams = other.m_fromParams;
	m_toParams = other.m_toParams;
	m_fromFlowPoint = other.m_fromFlowPoint;
	m_toFlowPoint = other.m_toFlowPoint;
}

//operators
const MCGraph& MCGraph::operator =(const MCGraph& other)
{
	copyFrom(other);
	return *this;
}