#include <vector>
#include <string>

#include <iostream>

#include "exception.hpp"
#include "utilities.hpp"
#include "variables.hpp"
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

vector<string> Code::get_args(char* argv[], vector<string> line, Variables vars, Line* lines)
{
	vector<string> args;

	for (int i = 1; i < line.size(); i++)
	{
		if (line[i] == "newl")
			args.push_back("\n");

		else if (line[i][0] == '\"')
		{
			string full = "";

			for (int o = i; o < line.size(); o++)
			{
				full += line[o] + ' ';

				if (line[o][line[o].size() - 1] == '\"')
				{
					i = o;
					break;
				}
			}

			full.erase(0, 1);
			full.erase(full.size() - 2);

			args.push_back(full);
		}

		else if (line[i][0] == '*')
		{
			line[i].erase(0, 1);
			
			if (vars.exist(line[i]))
				args.push_back(vars.get_value(line[i]));

			else
			{
				Exception::_var_not_found(*lines, line[i]);
				lines->abort = true;
			}
		}

		else if (line[i][0] == '%')
		{
			line[i].erase(0, 1);

			args.push_back(argv[stoi(line[i]) + 1]);
		}

		else
			args.push_back(line[i]);
	}

	return args;
}