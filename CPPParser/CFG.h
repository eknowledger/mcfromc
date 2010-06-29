#pragma once

#include "FlowPoint.h"
#include <list>
#include <vector>
#include <ostream>

typedef std::pair<FlowPoint*, FlowPoint*> Edge;
typedef std::list<FlowPoint*> FlowPointList;
typedef std::pair<FlowPoint*, FlowPointList> FlowPointAndNeighbors;
typedef std::list<FlowPoint*>::iterator FlowPointIterator;



//////////////////////////////////////////////////////////////////////////
// Control Flow Graph class. Represents an adjacency list of Flow Points.
//////////////////////////////////////////////////////////////////////////
class CFG
{
public:
	CFG(void);
	virtual ~CFG(void);

	FlowPoint* AddFlowPoint(SNode* node, std::string name);
	FlowPoint* AddFlowPoint(FlowPoint* fp);
	FlowPoint* RemoveFlowPoint(FlowPoint* fp);
	void AddEdge(Edge e);
	void RemoveEdge(Edge e);
	bool isEdge(Edge e);
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
};
