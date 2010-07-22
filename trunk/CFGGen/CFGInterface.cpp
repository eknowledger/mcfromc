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

void ComputFlowPointVisualData(CFG& cfg, std::vector<FlowPointVisualData>& fpData)
{
	std::vector<FlowPoint*> fps = cfg.flowPoints();
	for (size_t i = 0; i < fps.size(); ++i) {
		SNode* node = fps[i]->syntaxNode();
		std::string nodeText;
		int codeRow = -1;
		int codeCol = -1;
		if (fps[i]->Type() == FlowPoint::EXPRESSION_BLOCK)
		{
			std::vector<FlowPoint*> exprs = ((Block*)fps[i])->flowPoints();
			for (size_t j = 0; j < exprs.size(); ++j)
			{
				nodeText += exprs[j]->syntaxNode()->Text() + ";  ";
			}
		}	
		else if (node)
		{
			nodeText = node->Text();
			codeRow = node->codeRow();
			codeCol = node->codeColumn();
		}

		if (node || nodeText.size() > 0)
		{
			fpData.push_back(FlowPointVisualData(codeRow, 
				codeCol,
				fps[i]->index(),
				cfg.getName(fps[i]),
				nodeText));	
		}
	}
}


void generateCFG(std::string cfilename, std::vector<FlowPointVisualData>& fpData, std::ostream& ostr)
{	
	lastError = "";
	fpData.clear();
	NodeData* root = NULL;
	if (parseSyntax((char*)cfilename.c_str(), &root)==0 && root) {
		SNode* sroot = SyntaxNodeFactory::the().createNode(root);
		CFG cfg;
		Syntax2CFG(sroot, cfg).execute();
		CFGExprEvaluator(cfg).Evaluate();

		ComputFlowPointVisualData(cfg, fpData);
		cfg.printForDot(ostr);

		delete sroot;
	}
	else {
		lastError = "Code parsing failed. Check syntax.\n";
	}
}

std::string getLastError()
{
	return lastError;
}
