#include "SyntaxParserInterface.h"
#include "SNode.h"

int main(int argc, char** argv)
{
	Node* root;
	parseSyntax(argv[1], &root);
	SNode sroot(*root);

	return 0;
}