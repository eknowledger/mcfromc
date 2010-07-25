#include "SyntaxParserInterface.h"
#include "SNode.h"
#include <iostream>
#include <fstream>
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


bool generateCFG(std::string cfilename, std::vector<FlowPointVisualData>& fpData, std::ostream& ostr)
{	
	bool rc = true;
	lastError = "";
	fpData.clear();
	NodeData* root = NULL;
	std::string logFileName = cfilename + ".log";
	if (parseSyntax((char*)cfilename.c_str(), &root, (char*)logFileName.c_str())==0 && root) {
		SNode* sroot = SyntaxNodeFactory::the().createNode(root);
		CFG cfg;
		Syntax2CFG(sroot, cfg).execute();
		CFGExprEvaluator(cfg).Evaluate();

		ComputFlowPointVisualData(cfg, fpData);
		cfg.printForDot(ostr);

		delete sroot;
	}
	else {
		rc = false;
		std::string errorMessage;
		std::ifstream fileStream(logFileName.c_str());
		char buf[256];
		while (!fileStream.eof())
		{
			fileStream.getline(buf,256);
			if (strlen(buf) > 0)
			{
				errorMessage += std::string(buf) + "\n"; 
			}
			if (fileStream.gcount() == 0)
				break;
		}
		fileStream.close();
		lastError = std::string(errorMessage);
	}

	return rc;
}

std::string getLastError()
{
	return lastError;
}
