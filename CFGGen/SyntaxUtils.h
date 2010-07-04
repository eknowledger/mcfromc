#pragma once

class SNode;

class SyntaxUtils
{
public:
	static bool isLoop( SNode* node);
	static bool isForLoop( SNode* node);
	static bool isDoWhileLoop( SNode* node);
	static bool isWhileLoop( SNode* node);
	static bool isIfBranch( SNode* node);
	static bool isIfElseBranch( SNode* node);
	static bool isBranch( SNode* node);
	static bool isExpressionsOnlyStatement(SNode* statementNode);
	static bool isExpression(SNode* node);
	static bool isStatement(SNode* node);

private:
	SyntaxUtils(void);
	virtual ~SyntaxUtils(void);
};
