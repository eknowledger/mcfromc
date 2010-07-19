#include "SyntaxParserInterface.h"
#include "SNode.h"
#include <iostream>
#include <conio.h>
#include "SyntaxNodeFactory.h"
#include "SyntaxSimplifier.h"
#include "Syntax2CFG.h"
#include "CFG.h"
#include "CFGInterface.h"
#include "cfgexprevaluator.h"

std::string lastError;

std::vector<FlowPointVisualData> generateCFG(std::string cfilename, std::ostream& ostr)
{	
	lastError = "";
	std::vector<FlowPointVisualData> fpData;
	NodeData* root = NULL;
	if (parseSyntax((char*)cfilename.c_str(), &root)==0 && root) {
		SNode* sroot = SyntaxNodeFactory::the().createNode(root);
		CFG cfg;
		Syntax2CFG(sroot, cfg).execute();
		CFGExprEvaluator(cfg).Evaluate();
		cfg.printForDot();
		std::vector<FlowPoint*> fps = cfg.flowPoints();
		for (size_t i = 0; i < fps.size(); ++i) {
			SNode* node = fps[i]->syntaxNode();
			if (node) {
				fpData.push_back(FlowPointVisualData(node->codeRow(), 
													 node->codeColumn(),
													 fps[i]->index(),
													 cfg.getName(fps[i])));
			}
		}

		cfg.printForDot(ostr);

		//std::cout << *sroot;
		delete sroot;
	}
	else {
		lastError = "Code parsing failed. Check syntax.\n";
	}

	return fpData;
}

std::string getLastError()
{
	return lastError;
}
