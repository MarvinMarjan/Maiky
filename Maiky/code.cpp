#include <vector>
#include <string>

#include "utilities.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

vector<string> Code::get_code_block(Line& lines, int start)
{
	vector<string> block;

	for (int i = start; i < lines.get_size(); i++)
	{
		block.push_back(lines[i]);
		
		if (lines[i + 1] == "end")
			break;
	}

	return block;
}

string Code::remove_start_space(string source)
{
	int i = 0;

	while (true)
	{
		if (source[i] == ' ' || source[i] == '\t') // \t = tab
			source.erase(i, 1);

		else
			break;
	}

	return source;
}

vector<string> Code::get_args(vector<string> line)
{
	vector<string> args;

	for (int i = 1; i < line.size(); i++)
	{
		args.push_back(line[i]);
	}

	return args;
}