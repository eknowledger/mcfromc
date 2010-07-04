#include "SyntaxParserInterface.h"
#include "SNode.h"
#include <iostream>
#include <conio.h>
#include "SyntaxNodeFactory.h"
#include "SyntaxSimplifier.h"
#include "Syntax2CFG.h"
#include "CFG.h"
#include "CFGInterface.h"

std::vector<FlowPointVisualData> generateCFG(std::string cfilename)
{	
	std::vector<FlowPointVisualData> fpData;
	NodeData* root = NULL;
	parseSyntax((char*)cfilename.c_str(), &root);
	if (root) {
		SNode* sroot = SyntaxNodeFactory::the().createNode(root);
		CFG cfg;
		Syntax2CFG(sroot, cfg).execute();
		cfg.printForDot();
		std::vector<FlowPoint*> fps = cfg.flowPoints();
		for (size_t i = 0; i < fps.size(); ++i) {
			SNode* node = fps[i]->syntaxNode();
			if (node) {
				fpData.push_back(FlowPointVisualData(node->codeRow(), 
													 node->codeColumn(),
													 fps[i]->index(),
													 fps[i]->name()));
			}
		}

		//std::cout << *sroot;
		delete sroot;
	}
	else {
		std::cout << "parsing failed !\n";
	}

	return fpData;
}