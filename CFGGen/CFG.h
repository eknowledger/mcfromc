#pragma once

#include "FlowPoint.h"
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "CommonGraphDefs.h"
#include <list>
#include <vector>
#include <ostream>

typedef std::pair<FlowPoint*, FlowPoint*> Edge;
typedef std::list<FlowPoint*> FlowPointList;
typedef std::pair<FlowPoint*, FlowPointList> FlowPointAndNeighbors;
typedef std::list<FlowPoint*>::iterator FlowPointIterator;


typedef std::set<FPSharedPtr> FPSet;

//////////////////////////////////////////////////////////////////////////
// Control Flow Graph class. Represents an adjacency list of Flow Points.
//////////////////////////////////////////////////////////////////////////
class CFG: 
	public CFGBase
{
public:
	CFG(void);

	FlowPoint* AddFlowPoint(SNode* node, std::string name);
	FlowPoint* AddFlowPoint(FlowPoint* fp);
	FlowPoint* AddHiddenFlowPoint(SNode* node, std::string name);
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
	std::string getName(FlowPoint* fp);

private:
	FPSet m_knownFPs;
	FPSet m_hiddenFPs;
	typedef std::map<FlowPoint*,CFGBase::vertex_descriptor> FPToVertex;
	FPToVertex m_fpToV;
};