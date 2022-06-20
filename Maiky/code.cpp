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

vector<string> Code::get_args(vector<string> args, vector<string> line, Variables vars, Line* lines)
{
	vector<string> args_vec;

	for (int i = 1; i < line.size(); i++)
	{
		if (line[i] == "newl")
			args_vec.push_back("\n");

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

			args_vec.push_back(full);
		}

		else if (line[i][0] == '*')
		{
			line[i].erase(0, 1);

			if (!vars.exist(line[i]))
			{
				Exception::_var_not_found(*lines, line[i]);
				lines->abort = true;
			}

			else if (i + 1 < line.size() && line[i + 1] == "->")
			{
				if (i + 2 >= line.size())
				{
					Exception::_missing_attribute(*lines, line[i] + ' ' + line[i + 1]);
					lines->abort = true;
				}

				else if (i + 2 < line.size() && line[i + 2] == "type")
					args_vec.push_back(vars.get_type(line[i]));

				else
				{
					Exception::_undefined_attribute(*lines, line[i + 2]);
					lines->abort = true;
				}

				i += 2;
			}

			else
				args_vec.push_back(vars.get_value(line[i]));
		}

		else if (line[i][0] == '%')
		{
			line[i].erase(0, 1);

			args_vec.push_back(args[stoi(line[i]) - 1]);
		}

		else
			args_vec.push_back(line[i]);
	}

	return args_vec;
}