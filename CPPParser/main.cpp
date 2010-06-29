#include "SyntaxParserInterface.h"
#include "SNode.h"
#include <iostream>
#include <conio.h>
#include "SyntaxNodeFactory.h"
#include "SyntaxSimplifier.h"
#include "Syntax2CFG.h"
#include "CFG.h"

int main(int argc, char** argv)
{	
	if (argc < 2) {
		std::cout << "Usage: CPPParser [filename.c]\n";
		return 0;
	}

	NodeData* root = NULL;
	parseSyntax(argv[1], &root);
	if (root) {
		SNode* sroot = SyntaxNodeFactory::the().createNode(root);
		CFG cfg;
		Syntax2CFG(sroot, cfg).execute();
		cfg.printForDot();
		//std::cout << *sroot;
		delete sroot;
	}
	else {
		std::cout << "parsing failed !\n";
	}
	_getch();

	return 0;
}