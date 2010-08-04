#define _SCL_SECURE_NO_WARNINGS

#include "MCGraph.h"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/floyd_warshall_shortest.hpp"
#include "boost/graph/depth_first_search.hpp"
#include "boost/multi_array.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/detail/adjacency_list.hpp"

namespace{
	template<typename Graph, typename Edge>
	struct MCEdgeWriter
	{
		MCEdgeWriter(const Graph& g)
			: m_g(g)
		{}

		void operator()(std::ostream& out, const Edge& e) const
		{
			Order o = END_ORDER;
			std::string color;
			std::string backArrow;
			o = (Order) boost::get(boost::edge_weight,m_g,e);
			switch(o)
			{
			case GEQ: 
				color = "black";
				handleEqualEdge(e, backArrow);
				m_HandledEdges.insert(e);
				break;
			case GREATER:
				color = "red";
				break;
			default:
				_ASSERT(!"Arc with unknown weight");
			}
			out << "[color=\"" << color << "\"" << backArrow << "]";
		}

		void handleEqualEdge(Edge e, std::string& res) const
		{
			MCGraph::vertex_descriptor s = boost::source(e,m_g);
			MCGraph::vertex_descriptor t = boost::target(e,m_g);
			if (m_HandledEdges.find(boost::edge(t,s,m_g).first) != m_HandledEdges.end())
			{
				if (boost::edge(t,s,m_g).second)
				{
					res = ", dir=both, weight=1";
				}
			}
			else
			{
				res = ", style=invis, constraint=false, weight=0";
			}
		}

		mutable std::set<Edge> m_HandledEdges; 
		const Graph& m_g;
	};

	struct MCVertexWriter
	{
		MCVertexWriter(const MCGraph& g)
			: m_g(g)
		{}

		template <typename Vertex>
		void operator()(std::ostream& out, const Vertex& v) const
		{
			std::string name = boost::get(boost::vertex_name,m_g,v);
			out << "[label=\"" << name << "\", width=.2, height=.2, fontsize=16, font=Helvetica, shape=plaintext]";
		}

		const MCGraph& m_g;
	};
	struct MCGraphWriter {
		MCGraphWriter(const MCGraph& g)
			:m_g(g)
		{}

		void operator()(std::ostream& out) const {
			out << "label=" << 
				   m_g.getFriendlyName() << ";\nranksep=1.5;\nrankdir=LR;\nfont=Helvetica;\nfontsize=20;\nfontcolor=\"red\";\n";
			writeFlowPointParams(m_g.fromParams(),out);
			writeFlowPointParams(m_g.toParams(),out);
			if (m_g.fromParams().size() > 0 && m_g.fromParams().size() == m_g.toParams().size())
			{
				for (size_t i = 0; i < m_g.fromParams().size(); ++i)
				{
					MCGraph::edge_descriptor e;
					bool exists;
					boost::tie(e,exists) = boost::edge(i*2, i*2+1, m_g);
					if (!exists)
					{
						boost::tie(e,exists) = boost::edge(i*2+1, i*2, m_g);
						if (!exists)
						{
							//create invisible edges for layouting purposes
							out << i*2 << "->" << i*2+1 << " [style=invis];\n";
						}
					}
				}
			}
		}

		void writeFlowPointParams(const FlowPointParams& params, std::ostream& out) const
		{
			out << "{rank=same; ";
			for (FlowPointParams::const_iterator it = params.begin();
				it != params.end(); ++it) 
			{
				if (it != params.begin())
				{
					out << "; ";
				}
				out << *it;
			}

			out << "\n}\n";
		}

		const MCGraph& m_g;
	};
}

InvariantMember make_invariant(const MCBaseGraph::edge_descriptor& e,const MCGraph& g){
	MCBaseGraph::vertex_descriptor u,v; 

	//Gets the vertex that compose the edge
	u = boost::source(e,g);
	v = boost::target(e,g);
	//Gets the invariant parameters
	std::string x1Name,x2Name;
	Order o = END_ORDER;
	x1Name = boost::get(boost::vertex_name,g,u);
	x2Name = boost::get(boost::vertex_name,g,v);
	o = (Order) boost::get(boost::edge_weight,g,e);
	
	return boost::make_tuple(x2Name,o,x1Name);
}

MCConstrainEdge MCGraph::addEdgeFromInvariant(FPSharedPtr invFP,const InvariantMember& inv){
	ASSERT_RETURN(invFP != NULL,MCConstrainEdge());
	//Gets the vertex that are associated with the param names
	MCGraph::ParamNameToVertex::const_iterator x; 
	MCGraph::ParamNameToVertex::const_iterator y;
	//update the parameter names to have ' suffix if this is that target FP.
	if(invFP == m_fromFlowPoint.lock()){
		x = m_nameToVertex.find(inv.get<0>());
		y = m_nameToVertex.find(inv.get<2>());
	}
	else{
		x = m_nameToVertex.find(inv.get<0>() + "'");
		y = m_nameToVertex.find(inv.get<2>() + "'");
	}
	MCBaseGraph::edge_descriptor invEdge;
	ASSERT_RETURN(x != m_nameToVertex.end() && y != m_nameToVertex.end(),invEdge);
	//Gets the order.
	Order o = inv.get<1>();
	ASSERT_RETURN(o != END_ORDER,invEdge);
	//we do y -> to x since x < y means there is an edge from y to x
	invEdge = addOrUpdateEdge(x->second,y->second,o);
	return invEdge;
}

MCConstrainEdge MCGraph::addTrnasitionVariant(const TransitionVariant& t_var)
{
	ParamName tgtParam = t_var.get<2>() + "'";
	MCGraph::ParamNameToVertex::const_iterator x = m_nameToVertex.find(t_var.get<0>());
	MCGraph::ParamNameToVertex::const_iterator y = m_nameToVertex.find(tgtParam);
	MCConstrainEdge tVarEdge;
	ASSERT_RETURN(x != m_nameToVertex.end() && y != m_nameToVertex.end(),tVarEdge);
	//Gets the order.
	Order o = t_var.get<1>();
	ASSERT_RETURN(o != END_ORDER,tVarEdge);
	//we do y -> to x since x < y means there is an edge from y to x
	tVarEdge = addOrUpdateEdge(y->second,x->second,o);
	return tVarEdge;
}

void MCGraph::removeEdgeFromInvariant(FPSharedPtr invFP,const InvariantMember& inv)
{
	ASSERT_RETURN_VOID(invFP != NULL);
	//Gets the vertex that are associated with the param names
	MCGraph::ParamNameToVertex::const_iterator x;
	MCGraph::ParamNameToVertex::const_iterator y;
	//update the parameter names to have ' suffix if this is that target FP.
	if(invFP == m_fromFlowPoint.lock()){
		x = m_nameToVertex.find(inv.get<0>());
		y = m_nameToVertex.find(inv.get<2>());
	}
	else{
		x = m_nameToVertex.find(inv.get<0>() + "'");
		y = m_nameToVertex.find(inv.get<2>() + "'");
	}
	ASSERT_RETURN_VOID(x != m_nameToVertex.end() && y != m_nameToVertex.end());
	//remove the edge from the graph.
	boost::remove_edge(y->second,x->second,*this);

}

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
		std::string srcName,trgName;
		//Gets the name of the parameterts and order to make Invariant Member.

		resInvariant.insert(make_invariant(*edge,*this));
	}
	return resInvariant;
}

std::ostream& operator <<(std::ostream& out,const MCGraph& mc)
{
	out << std::endl;
	std::stringstream sMC;
	boost::property_map<MCBaseGraph,boost::vertex_name_t>::const_type vNameProp = get(boost::vertex_name,mc);
	boost::write_graphviz(sMC,mc,MCVertexWriter(mc),MCEdgeWriter<MCGraph,MCGraph::edge_descriptor>(mc),MCGraphWriter(mc));
	out << sMC.str().c_str();
	out << std::endl;
	return out;
}

//************************************
// Method:    writeParamsInCLSFormat
// FullName:  MCGraph::writeParamsInCSLFormat
// Access:    public 
// Returns:   void
// Parameter: std::ostream & out
// Parameter: const FlowPointParams & fpParams
//************************************
void MCGraph::writeParamsInCSLFormat(std::ostream& out,const FlowPointParams& fpParams)
{
	for(FlowPointParams::const_iterator paramItr = fpParams.begin(); paramItr != fpParams.end(); ++paramItr){
		if (paramItr != fpParams.begin())
		{
			out << ",";
		}
		out << boost::get(boost::vertex_name,*this,*paramItr);
	}
}

///************************************
/// Method:    writeInCSLFormat
/// Access:    public 
/// Returns:   void
/// Description: Writes MC to output stream in Chin Sun-Lee's MC format.
/// Parameter: std::ostream & out
///************************************
void MCGraph::writeInCSLFormat(std::ostream& out)
{
	std::string fromFP = m_fromFlowPoint.lock()->getFriendlyName();
	std::string toFP = m_toFlowPoint.lock()->getFriendlyName();

	out << fromFP << "(";
	writeParamsInCSLFormat(out,m_fromParams);
	out << ") :- [";
	MCGraph::edge_iterator eIt, eEnd, eBegin;
	boost::tie(eBegin, eEnd) = boost::edges(*this);
	eIt = eBegin;
	while (eIt != eEnd)
	{
		std::string src = boost::get(boost::vertex_name,*this,boost::source(*eIt, *this));
		std::string tgt = boost::get(boost::vertex_name,*this,boost::target(*eIt, *this));
		Order o = (Order)boost::get(boost::edge_weight,*this,*eIt);
		if (eIt != eBegin)
		{
			out << ",";
		}
		out << boost::make_tuple(src, o, tgt);
		++eIt;
	}
	out << "] ; " << toFP << "(";
	writeParamsInCSLFormat(out,m_toParams);
	out << ")\n";
}

MCGraph::edge_descriptor MCGraph::addOrUpdateEdge(vertex_descriptor u,vertex_descriptor v,Order o)
{
	bool exists = false;
	vertex_descriptor source(u),target(v);
	
	//gets the real source and target of edge.
	switch(o){
		case GREATER:
		case GEQ:
			break;
		//stays the same
		case LESS:
			source = v;
			target = u;
			o = GREATER;
			break;
		case LEQ:
			source = v;
			target = u;
			o = GEQ;
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
	else if (o != EQ) {
		return add_edge(source,target,o,*this).first;
	}
	else {
		add_edge(target,source,GEQ,*this);
		return add_edge(source,target,GEQ,*this).first;
	}
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
		addEdgeFromInvariant(fWeak.lock(),*invItr);
	
}

void MCGraph::copyFrom(const MCGraph& other)
{
	*((MCBaseGraph*)this) = (MCBaseGraph) other;
	m_nameToVertex = other.m_nameToVertex;
	m_fromParams = other.m_fromParams;
	m_toParams = other.m_toParams;
	m_fromFlowPoint = other.m_fromFlowPoint;
	m_toFlowPoint = other.m_toFlowPoint;
}

MCGraph::vertex_descriptor MCGraph::addVertexForVar(const ParamName& varName)
{
	//make sure the same var is not already in graph.
	ParamNameToVertex::const_iterator alreadyInItr = m_nameToVertex.find(varName);
	ASSERT_RETURN(alreadyInItr == m_nameToVertex.end(),MCGraph::vertex_descriptor());
	MCGraph::vertex_descriptor v = boost::add_vertex(*this);
	boost::put(boost::vertex_name,*this,v,varName);
	m_nameToVertex[varName] = v;

	return v;
}

void MCGraph::addVar(const ParamName& var)
{
	ParamName vTgtName = var + "'";
	//adds the vertices to graph
	MCGraph::vertex_descriptor srcVar = addVertexForVar(var);
	MCGraph::vertex_descriptor tgtVar = addVertexForVar(vTgtName);
	//update the data structures
	m_fromParams.insert(srcVar);
	m_toParams.insert(tgtVar);
}

void MCGraph::addVariables(const ParamNameSet& vars)
{
	for(ParamNameSet::const_iterator varItr = vars.begin(); varItr != vars.end(); ++varItr){
		addVar(*varItr);
	}
}

void MCGraph::addConstants(const VarToValue& consts)
{
	for(VarToValueIt it = consts.begin(); it != consts.end(); ++it){
		addVar((*it).first);
	}
}

//operators
const MCGraph& MCGraph::operator =(const MCGraph& other)
{
	copyFrom(other);
	return *this;
}

