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
#include "UniqueObjectIdMgr.h"
#include <stdlib.h>
#include <string>

std::string lastError;

/// Test function for generating random edges on all MCs of CFG
void testGenerateMCEdges(CFG& cfg)
{
	for (MCSet::const_iterator it = cfg.KnownMCs().begin();
		it != cfg.KnownMCs().end(); ++it)
	{
		MCSharedPtr spMC = *it;

		size_t numVars = cfg.Variables().size();
		size_t numEdges = rand() % numVars;
		for (size_t i = 0; i < numEdges; ++i)
		{
			size_t varA = rand() % numVars;
			size_t varB = rand() % numVars;
			if (varA != varB)
			{
				std::string nameA;
				std::string nameB;
				size_t index = 0;
				for (ParamNameSet::const_iterator vit = cfg.Variables().begin();
					vit != cfg.Variables().end(); ++vit, ++index)
				{
					if (index == varA)
						nameA = *vit;
					if (index == varB)
						nameB = *vit;

				}
				if (rand() % 2)
					nameA += "'";
				if (rand() % 2)
					nameB += "'";
				spMC->addEdgeFromInvariant(InvariantMember( nameA, (Order) (rand()%5-1), nameB));
			}

		}
	}
}
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

/// Method:    generateCFG
/// FullName:  generateCFG
/// Access:    public 
/// Returns:   bool
/// Description: Generates the CFG and MCs.
/// Parameter: std::string cfilename
///					The input C file name.
/// Parameter: std::vector<FlowPointVisualData> & fpData
///					Generated CFG flow points visual data vector
///					The visual data includes text of the relevant code and FP name.
/// Parameter: std::ostream & gvOstr
///					graphViz output stream for generation of the CFG bitmap.
/// Parameter: std::ostream & mcOstr
///					Montonicity Constraints graph output stream (Ariel's format).
/// Parameter: StrPairVector & mcStrs
///					A vector of string pairs. Each pair is a matching between
///					a MC name and the graphViz text input for generating the MC
///					graph bitmap.
bool generateCFG(std::string cfilename, std::vector<FlowPointVisualData>& fpData, 
				 std::ostream& gvOstr, std::ostream& mcOstr, StrPairVector& mcStrs)
{	
	bool rc = true;
	lastError = "";
	fpData.clear();
	UniqueObjectIdMgr::Reset();
	NodeData* root = NULL;
	std::string logFileName = cfilename + ".log";
	if (parseSyntax((char*)cfilename.c_str(), &root, (char*)logFileName.c_str())==0 && root) {
		SNode* sroot = SyntaxNodeFactory::the().createNode(root);
		rc = (lastError.size() == 0);
		if (rc)
		{		
			CFG cfg;
			Syntax2CFG(sroot, cfg).execute();
			CFGExprEvaluator(cfg).Evaluate();

			ComputFlowPointVisualData(cfg, fpData);
			cfg.printForDot(gvOstr);
			//////////////////////////////////////////////////////////////////////////
			//**** Test - uncomment next line to test MCs output ***
			//testGenerateMCEdges(cfg);
			//////////////////////////////////////////////////////////////////////////
			for (MCSet::const_iterator it = cfg.KnownMCs().begin();
				 it != cfg.KnownMCs().end(); ++it)
			{
				MCSharedPtr spMC = *it;
				std::ostringstream ostr;
				ostr << *spMC;
				std::string wstr = ostr.str();
				if (wstr.size() > 0)
				{
					std::string str;			
					str.assign(wstr.begin(), wstr.end());
					mcStrs.push_back(StrPair((*it)->getFriendlyName(), str));
				}
				spMC->writeInCSLFormat(mcOstr);
			}
		}

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

// Method:    getLastError
// FullName:  getLastError
// Access:    public 
// Returns:   std::string
// Description: Gets the last error string from the Syntax Parser.
std::string getLastError()
{
	return lastError;
}
