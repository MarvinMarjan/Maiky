#include <vector>
#include <string>

#include "code.hpp"
#include "line.hpp"

using namespace std;

vector<string> Code::get_code_block(Line lines, int start)
{
	vector<string> block;

	for (int i = start; i < lines.get_size(); i++)
	{
		if (lines[i] == "end")
			break;

		else
			block.push_back(lines[i]);
	}

	return block;
}

string Code::remove_start_space(string source)
{
	for (int i = 0; i < source.size(); i++)
	{
		if (source[i] == ' ')
			source.erase(i, i);

		else
			break;
	}

	return source;
}