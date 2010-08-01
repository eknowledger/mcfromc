#pragma once
#include <SyntaxParserInterface.h>

class SNode;

//////////////////////////////////////////////////////////////////////////
/// Singleton factory for Syntax Nodes. 
/// Note that it is not currently thread safe !
/// (since it uses local static variable inside the 'the()' method). 
//////////////////////////////////////////////////////////////////////////
class SyntaxNodeFactory
{
public:
	virtual ~SyntaxNodeFactory(void);

	static SyntaxNodeFactory& the();

	SNode* createNode(NodeData* n); 

private:
	SyntaxNodeFactory(void);
	SyntaxNodeFactory(const SyntaxNodeFactory& other);
	SyntaxNodeFactory& operator=(const SyntaxNodeFactory& other);
	void IssueInvalidExpressionError( SNode* node );

};
