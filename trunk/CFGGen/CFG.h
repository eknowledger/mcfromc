#pragma once

#include "FlowPoint.h"
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "CommonGraphDefs.h"
#include "MCGraph.h"
#include <list>
#include <vector>
#include <ostream>

typedef std::pair<FlowPoint*, FlowPoint*> Edge;
typedef std::list<FlowPoint*> FlowPointList;
typedef std::pair<FlowPoint*, FlowPointList> FlowPointAndNeighbors;
typedef std::list<FlowPoint*>::iterator FlowPointIterator;


typedef std::set<FPSharedPtr> FPSet;
typedef std::set<MCSharedPtr> MCSet;

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
	MCSharedPtr AddEdge(FlowPoint* f,FlowPoint* g);
	void RemoveEdge(FlowPoint* f,FlowPoint* g);
	void MarkEdgeAsInvariantTrue(FlowPoint* f,FlowPoint* g, bool truthValue);
	bool isEdge(FlowPoint* f,FlowPoint* g);
	FlowPointList neighbors(FlowPoint* fp);
	FlowPointList ancestors(FlowPoint* fp);
	std::vector<FlowPoint*> flowPoints();
	//prints graph edges in GraphViz Dot format to std::cout
	void printForDot();
	//prints graph edges in GraphViz Dot format to given output stream
	void printForDot(std::ostream& ostr);
	std::string getName(FlowPoint* fp);

	inline FlowPoint* Start() const
	{
		return m_startFP;
	}
	inline void SetStart(FlowPoint* startFP)
	{
		m_startFP = startFP;
	}

	inline void AddVariable(const ParamName& varName)
	{
		m_knownVariables.insert(varName);
	}

	inline const ParamNameSet& Variables() const
	{
		return m_knownVariables;
	}

	void AddConstant(ValType value);

	inline const VarToValue& Constants() const
	{
		return m_knownConstants;
	}

	inline const MCSet& KnownMCs() const
	{
		return m_knwonMCs;
	}
	void UpdateTransitionsWithVars();
	void PerformLogicalClousures(bool removeUnsatisfiable);
	void AssignFlowPointIDs();

protected:
	void removeEdgeHelper(edge_descriptor e);

private:
	FPSet m_knownFPs;
	FPSet m_hiddenFPs;
	FlowPoint* m_startFP;
	//MCs on the graph
	MCSet m_knwonMCs;
	ParamNameSet m_knownVariables;
	VarToValue m_knownConstants; 
};