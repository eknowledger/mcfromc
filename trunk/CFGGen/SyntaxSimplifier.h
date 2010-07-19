#pragma once

class SNode;

class SyntaxSimplifier
{
public:
	SyntaxSimplifier(SNode* root);
	virtual ~SyntaxSimplifier(void);

	void execute();

private:
	void reduceChildren(SNode* node);
	void expandForLoops(SNode* node);


	SNode* m_root;
};
