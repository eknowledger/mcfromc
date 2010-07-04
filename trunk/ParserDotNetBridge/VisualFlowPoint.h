// ParserDotNetBridge.h

#pragma once

#include <iostream>
#include "CFGInterface.h"
#include <stdlib.h>
#include <vcclr.h>

using namespace System;

///this project serves as an inter-op between the native C++ projects and
///.NET applications code.
namespace ParserDotNetBridge {

	///This class wraps a CFG flow point (it represents it's visual attributes)
	public ref class VisualFlowPoint
	{
	public:
		property String^ Name {
			String^ get() {
				return m_Name;
			}
		}
		property int Column {
			int get() {
				return m_col;
			}
		}
		property int Row {
			int get() {
				return m_row;
			}
		}
	internal:
		VisualFlowPoint(FlowPointVisualData creationData)
		{
			m_Name = gcnew String(creationData.name.c_str());
			m_Name = m_Name->Concat(m_Name, Int32(creationData.index).ToString());
			m_row = creationData.row;
			m_col = creationData.col;
		}

	private:
		String^ m_Name;
		int m_row;
		int m_col;

	};
}
