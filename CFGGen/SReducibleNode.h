#pragma once
#include "snode.h"

//////////////////////////////////////////////////////////////////////////
/// Represents a syntax node which can and should be reduced it the final
/// Abstract Syntax Tree. An example of such nodes could be Statement Lists,
/// Compound Statements, Declarations, or any other syntactic element which
/// is not taking part in the CFG and MC analysis.
/// It's ShouldBeReduced interface is used by the SyntaxSimplifier class.
//////////////////////////////////////////////////////////////////////////
class SReducibleNode : public SNode
{
public:
	SReducibleNode(const NodeData& node): SNode(node)
	{
	}

	virtual ~SReducibleNode(void);

	virtual bool ShouldBeReduced();
};
