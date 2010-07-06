// ParserDotNetBridge.h

#pragma once

#include <iostream>
#include "CFGInterface.h"
#include <stdlib.h>
#include <vcclr.h>

using namespace System;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;

///this project serves as an inter-op between the native C++ projects and
///.NET applications code.
namespace ParserDotNetBridge {
	public ref class CFGParser abstract sealed
	{
		static bool To_CharStar( String^ source, char*& target );
		static bool To_string( String^ source, std::string &target);

	public:
		static ArrayList^ GenerateCFG(String^ cfilename, [Out] String^% graphText);
		static String^ GetLastError();
	};
}
