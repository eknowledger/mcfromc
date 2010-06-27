#pragma once

#include "FlowPoint.h"
#include <list>

typedef std::pair<FlowPoint*, FlowPoint*> Edge;
typedef std::list<FlowPoint*> FlowPointList;
typedef std::pair<FlowPoint*, FlowPointList> FlowPointAndNeighbors;
typedef std::list<FlowPoint*>::iterator FlowPointIterator;

class Block;

class CFG
{
public:
	CFG(void);
	virtual ~CFG(void);

	FlowPoint* AddFlowPoint(SNode* node, std::string name);
	Block* AddBlock(SNode* statement, std::string name);
	FlowPoint* RemoveFlowPoint(FlowPoint* fp);
	void AddEdge(Edge e);
	void RemoveEdge(Edge e);
	bool isEdge(Edge e);
	void print();
	FlowPointList neighbors(FlowPoint* fp);
	
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
