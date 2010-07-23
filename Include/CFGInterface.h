#pragma once

#include <string>
#include <vector>
#include <ostream>

struct FlowPointVisualData
{
	int row;
	int col;
	int index;
	std::string name;
	std::string text;

	FlowPointVisualData(int _row, int _col, int _index, const std::string& _name,
						const std::string& _text):
		row(_row), col(_col), index(_index), name(_name), text(_text)
	{
	}
};

bool generateCFG(std::string cfilename, 
				 std::vector<FlowPointVisualData>& fpData, 
				 std::ostream& ostr);

std::string getLastError();
