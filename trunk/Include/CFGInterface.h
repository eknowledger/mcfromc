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

	FlowPointVisualData(int _row, int _col, int _index, const std::string& _name):
		row(_row), col(_col), index(_index), name(_name)
	{
	}
};

std::vector<FlowPointVisualData> generateCFG(std::string cfilename, std::ostream& ostr);
