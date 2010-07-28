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

	///returns an ArrayList of VisualFlowPoints read and parsed from the C file.
	ArrayList^ CFGParser::GenerateCFG(String^ cfilename, 
									[Out] String^% graphText, 
									[Out] ArrayList^% mcGraphNames,
									[Out] ArrayList^% mcGraphTexts)
	{
		ArrayList^ arr = gcnew ArrayList();
		std::string fname;
		To_string(cfilename, fname);
		std::ostringstream ostr;
		StrPairVector mcStrs;
		std::vector<FlowPointVisualData> fpData;
		mcGraphTexts = gcnew ArrayList();
		mcGraphNames = gcnew ArrayList();
		if (generateCFG(fname, fpData, ostr, mcStrs)) {
			std::string graphTextStr = ostr.str();
			graphText = gcnew String(graphTextStr.c_str());
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