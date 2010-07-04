#include "stdafx.h"
#include "CFGParser.h"
#include "VisualFlowPoint.h"

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
	ArrayList^ CFGParser::GenerateCFG(String^ cfilename)
	{
		ArrayList^ arr = gcnew ArrayList();
		std::string fname;
		To_string(cfilename, fname);
		std::vector<FlowPointVisualData> fpData = generateCFG(fname);
		for (size_t i = 0; i < fpData.size(); ++i) {
			arr->Add(gcnew VisualFlowPoint(fpData[i]));
		}

		return arr;
	}
}