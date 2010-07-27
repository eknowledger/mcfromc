#pragma once

#include "CFG.h"
#include "ExprMgr.h"
#include <boost/graph/depth_first_search.hpp>
#include <vector>
#include "CommonGraphDefs.h"

class FlowPoint;

class CFGExprEvaluator
{
public:
	CFGExprEvaluator(CFG& cfg) : m_cfg(cfg){}

	void Evaluate();

private:

	class ExprEvalVisitor: public boost::default_dfs_visitor 
	{
	public:
		ExprEvalVisitor()
		{
		}

		template <typename Edge, typename Graph>
		void examine_edge(Edge u, const Graph& g);

		template < typename Vertex, typename Graph >
		void discover_vertex(Vertex u, const Graph & g) const;

		template < typename Vertex, typename Graph >
		void finish_vertex(Vertex u, const Graph & g) const
		{
		}

	private:
		SPExpr evaluateAssignmentExpr(SNode* expr) const;
		void evaluateExprFlowPoint(FlowPoint* expressionBlock, FlowPoint* fp) const;
		void evaluateBranchInvariants(FlowPoint* fp) const;
		void findRelevantSubConditions(SNode* node, 
									   std::vector<SNode*>& subConditions) const;
		InvariantMember computeExprInvariant(const BinExpr& expr) const;
		Order order(OperatorType opType) const;
		std::wstring StringToWString(const std::string& s) const;
		Invariant ComputeExprBlockInvariants(VarToValue& inValue, VarToValue& outValue) const;
	};

	CFG& m_cfg;
};
