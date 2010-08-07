#pragma once

#include "GeneralMacros.h"
#include "CommonDefs.h"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_matrix.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include <iostream>
#include <string>
#include <atlbase.h>
#include <atlconv.h>

enum Order{
	LESS = -4,		/* <							*/
	LEQ,			/* <=							*/
	EQ,				/* =							*/
	GREATER = -1,	/* >							*/
	GEQ,			/* >=							*/
	END_ORDER		/* Indicates there is no order	*/
};

//forward declaration
class MCGraph;
class FlowPoint;

typedef boost::weak_ptr<MCGraph> MCWeakPtr;
typedef int MCEdgeWeight;

typedef boost::property<boost::graph_name_t,std::string>
		MCGraphProp;


typedef boost::adjacency_list<boost::listS															//container class of the edges.
							 ,boost::vecS															//container class for the vertices
							 ,boost::directedS														//specifies if this is directo/undirected graph
							 ,boost::property<boost::vertex_name_t,std::string> 					//Property of the vertices
							 ,boost::property<boost::edge_weight_t,MCEdgeWeight>					//Property of the edges
							 ,MCGraphProp>															//Property of the graph
		MCBaseGraph;
typedef MCBaseGraph::edge_descriptor MCConstrainEdge;


//C.F.G
//adds a property for the MC that will reside on the edges of the C.F.G
namespace boost{
	enum edge_sizeChange_t{edge_sizeChange};
	enum vertex_attachedFP_t{vertex_attachedFP};
	enum edge_invariantTrue_t{edge_invariantTrue};
	BOOST_INSTALL_PROPERTY(vertex,attachedFP);
	BOOST_INSTALL_PROPERTY(edge,sizeChange);
	BOOST_INSTALL_PROPERTY(edge,invariantTrue);
}

typedef boost::shared_ptr<FlowPoint> FPSharedPtr;
typedef boost::weak_ptr<FlowPoint> FPointWeakPtr;

typedef boost::property<boost::vertex_name_t,std::string,
						boost::property<boost::vertex_attachedFP_t,FPointWeakPtr,
						boost::property<boost::vertex_color_t, boost::default_color_type > > >
	CFGVertexProp;

typedef boost::property<boost::edge_sizeChange_t,MCWeakPtr					//Size change property on the edges is the weak pointer to the MC
					   ,boost::property<boost::edge_name_t,std::string,
						boost::property<boost::edge_invariantTrue_t,bool> > >	//Holds the name of the MC that holds the transition.
	CFGEdgeProp;

typedef boost::adjacency_list<boost::listS				//container class of the edges.
							 ,boost::vecS				//container class for the vertices
							 ,boost::bidirectionalS		//specifies if this is directo/undirected graph (used for in_edges) 
							 ,CFGVertexProp 			//Property of the vertices
							 ,CFGEdgeProp>				//Property of the edges
	CFGBase;

typedef CFGBase::vertex_descriptor FP_CFG_ID;


//Invariants
typedef boost::tuple<std::string,Order,std::string> InvariantMember;
typedef boost::tuple<std::string,Order,std::string> TransitionVariant;
typedef std::set<TransitionVariant> TransitionVariantSet;
typedef std::set<InvariantMember> Invariant;
typedef std::vector<InvariantMember> InvariantDiff;

//output operators.
namespace GraphWriters{
	template<class Name>
	class label_writer_w
	{
	public:
		label_writer_w(Name _name)
			: m_prop(_name)
		{}
		
		template<typename VertexOrEdge>
		void operator()(std::ostream& out, const VertexOrEdge& v) const {
			std::stringstream sProp;
			sProp << get(m_prop, v);
			out << "[label=\"" << sProp << "\"]";
		}
	protected:
		Name m_prop;

	};

	template <class Name>
	inline label_writer_w<Name>
		make_label_writer_w(Name n) {
			return label_writer_w<Name>(n);
	};
}

inline std::ostream& operator <<(std::ostream& out,Order o)
{
	switch(o)
	{
	case LESS: 
		out << "<";
		break;
	case LEQ:
		out << "<=";
		break;
	case EQ:
		out << "=";
		break;
	case GEQ:
		out << ">=";
		break;
	case GREATER:
		out << ">";
		break;
	case END_ORDER:
		out << "NA";
		break;
	default:
		ASSERT_RETURN(!"Unhandled order type",out);
	}
	return out;
}

inline std::istream& operator >>(std::istream& in,Order &o)
{
	std::string sOrder;	//Holds the order as string;
	in >> sOrder;
	if(sOrder == ">")
		o = GREATER;
	else if(sOrder == ">=")
		o = GEQ;
	else if(sOrder == "=")
		o = EQ;
	else if(sOrder == "<")
		o = LESS;
	else if(sOrder == "<=")
		o = LEQ;
	else if(sOrder == "NA")
		o = END_ORDER;
	else 
		ASSERT_RETURN(!"Unhandled order type",in);
	return in;
}

inline std::ostream& operator <<(std::ostream& out, const InvariantMember& inv)
{
	out << inv.get<0>();
	out << inv.get<1>();
	out << inv.get<2>();

	return out;
}

inline std::ostream& operator <<(std::ostream& out, const Invariant& inv)
{
	for(Invariant::const_iterator itr = inv.begin(); itr != inv.end(); ++itr)
		out << *itr;
	return out;
}

inline Invariant InvariantNotOp(const InvariantMember& inv)
{
	Order newOrd = END_ORDER;
	Invariant res;
	switch(inv.get<1>())
	{
	case LESS: 
		newOrd = GEQ;
		break;
	case LEQ:
		newOrd = GREATER;
		break;
	case EQ:
		//the result is an || expression so for now we do not handle it.
		return res;
		break;
	case GEQ:
		newOrd = LESS;
		break;
	case GREATER:
		newOrd = LEQ;
		break;
	default:
		ASSERT_RETURN(!"Unhandled order type",res);
	}
	res.insert(boost::make_tuple(inv.get<0>(),newOrd,inv.get<2>()));
	return res;
}