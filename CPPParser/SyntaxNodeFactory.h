#pragma once
#include <SyntaxParserInterface.h>

class SNode;

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
	
};
