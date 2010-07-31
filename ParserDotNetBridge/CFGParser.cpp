#include "stdafx.h"
#include "CFGParser.h"
#include "VisualFlowPoint.h"
#include <sstream>

namespace ParserDotNetBridge {
	bool CFGParser::To_CharStar( String^ source, char*& target )
	{
		pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		int len = (( source->Length+1) * 2);
		target = new char[ len ];
		return wcstombs( target, wch, len ) != -1;
	}

	bool CFGParser::To_string( String^ source, std::string &target )
	{
		pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		int len = (( source->Length+1) * 2);
		char *ch = new char[ len ];
		bool result = wcstombs( ch, wch, len ) != -1;
		target = ch;
		delete ch;
		return result;
	}

	/// Method:    GenerateCFG
	/// FullName:  ParserDotNetBridge::CFGParser::GenerateCFG
	/// Access:    public static 
	/// Returns:   ArrayList^
	/// Description: Generates the CFG and MCs
	/// Parameter: String ^ cfilename
	///					The C file name for parsing.
	/// Parameter: [Out] String ^ % graphText
	///					The output CFG in graphViz text format.
	/// Parameter: [Out] ArrayList ^ % mcGraphNames
	///					The output MC names
	/// Parameter: [Out] ArrayList ^ % mcGraphTexts
	///					The output MCs graphs in graphViz text format. 
	///					Has the same length as mcGraphNames.
	/// Parameter: [Out] ArrayList ^ % mcsText
	///					The output MCs in Ariel's text format.
	ArrayList^ CFGParser::GenerateCFG(String^ cfilename, 
									[Out] String^% graphText, 
									[Out] ArrayList^% mcGraphNames,
									[Out] ArrayList^% mcGraphTexts,
									[Out] String^% mcsText)
	{
		ArrayList^ arr = gcnew ArrayList();
		std::string fname;
		To_string(cfilename, fname);
		std::ostringstream gvOstr;
		std::ostringstream mcOstr;
		StrPairVector mcStrs;
		std::vector<FlowPointVisualData> fpData;
		mcGraphTexts = gcnew ArrayList();
		mcGraphNames = gcnew ArrayList();
		if (generateCFG(fname, fpData, gvOstr, mcOstr, mcStrs)) {
			std::string graphTextStr = gvOstr.str();
			std::string mcTextStr = mcOstr.str().c_str();
			graphText = gcnew String(graphTextStr.c_str());
			mcsText = gcnew String(mcTextStr.c_str());
			for (size_t i = 0; i < fpData.size(); ++i) {
				arr->Add(gcnew VisualFlowPoint(fpData[i]));
			}

			for (size_t i = 0; i < mcStrs.size(); ++i) {
				mcGraphNames->Add(gcnew String(mcStrs[i].first.c_str()));
				mcGraphTexts->Add(gcnew String(mcStrs[i].second.c_str()));
			}
		}

		return arr;
	}

	String^ CFGParser::GetLastError()
	{
		std::string lastError = getLastError();
		return gcnew String(lastError.c_str());
	}
}