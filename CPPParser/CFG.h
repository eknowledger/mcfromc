#pragma once

#include "FlowPoint.h"
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/graph/adjacency_list.hpp"
#include <list>
#include <vector>
#include <ostream>

typedef std::pair<FlowPoint*, FlowPoint*> Edge;
typedef std::list<FlowPoint*> FlowPointList;
typedef std::pair<FlowPoint*, FlowPointList> FlowPointAndNeighbors;
typedef std::list<FlowPoint*>::iterator FlowPointIterator;

//adds a property for the MC that will reside on the edges of the C.F.G
namespace boost{
	enum edge_sizeChange_t{edge_sizeChange};
	enum vertex_attachedFP_t{vertex_attachedFP};
	BOOST_INSTALL_PROPERTY(vertex,attachedFP);
	BOOST_INSTALL_PROPERTY(edge,sizeChange);
}

typedef boost::shared_ptr<FlowPoint> FPSharedPtr;
typedef std::set<FPSharedPtr> FPSet;

typedef boost::weak_ptr<FlowPoint> FPointWeakPtr;

typedef boost::property<boost::vertex_name_t,std::string,
					    boost::property<boost::vertex_attachedFP_t,FPointWeakPtr> >
	    CFGVertexProp;

typedef boost::weak_ptr<void> MCWeakPtr;

typedef boost::property<boost::edge_sizeChange_t,MCWeakPtr					//Size change property on the edges is the weak pointer to the MC
					   ,boost::property<boost::edge_name_t,std::string> >	//Holds the name of the MC that holds the transition.
CFGEdgeProp;

typedef boost::adjacency_list<boost::listS				//container class of the edges.
							 ,boost::vecS				//container class for the vertices
							 ,boost::bidirectionalS		//specifies if this is directo/undirected graph (used for in_edges) 
							 ,CFGVertexProp 			//Property of the vertices
							 ,CFGEdgeProp>				//Property of the edges
	CFGBase;



//////////////////////////////////////////////////////////////////////////
// Control Flow Graph class. Represents an adjacency list of Flow Points.
//////////////////////////////////////////////////////////////////////////
class CFG: 
	public CFGBase
{
public:
	CFG(void);
	virtual ~CFG(void);

	FlowPoint* AddFlowPoint(SNode* node, std::string name);
	FlowPoint* AddFlowPoint(FlowPoint* fp);
	void RemoveFlowPoint(FlowPoint* fp);
	void AddEdge(FlowPoint* f,FlowPoint* g);
	void RemoveEdge(FlowPoint* f,FlowPoint* g);
	bool isEdge(FlowPoint* f,FlowPoint* g);
	FlowPointList neighbors(FlowPoint* fp);
	std::vector<FlowPoint*> flowPoints();
	//prints graph edges in GraphViz Dot format to std::cout
	void printForDot();
	//prints graph edges in GraphViz Dot format to given output stream
	void printForDot(std::ostream& ostr);

private:
	struct Vertex : public FlowPointAndNeighbors {
		Vertex(FlowPoint* fp) {
			first = fp;
		}
		Vertex(FlowPoint* fp, const FlowPointList& fpList) {
			first = fp;
			second = fpList;
		}
	};

	std::list<Vertex>::iterator findFlowPoint(FlowPoint* fp);
	FlowPointIterator findFlowPoint(const std::list<Vertex>::iterator& fpList, 
									const FlowPoint* fp);

	std::list<Vertex> m_AdjList;
private:
	FPSet m_knownFPs;
	typedef std::map<FlowPoint*,CFGBase::vertex_descriptor> FPToVertex;
	FPToVertex m_fpToV;
};
