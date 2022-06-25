#include <vector>
#include <string>

#include <iostream>

#include "exception.hpp"
#include "utilities.hpp"
#include "variables.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

vector<string> Code::get_code_block(Line& lines, int* start)
{
	vector<string> block;
	bool in_another_block = false;

	for (int i = *start; i < lines.get_size(); i++)
	{
		block.push_back(lines[i]);

		if (lines[i] == "")
			continue;

		else if (Utils::split_string(lines[i])[0] == "if" || Utils::split_string(lines[i])[0] == "elif" || Utils::split_string(lines[i])[0] == "else" || Utils::split_string(lines[i])[0] == "while" || Utils::split_string(lines[i])[0] == "for")
		{
			i++;
			vector<string> other_block = Code::get_code_block(lines, &i);

			for (string i : other_block)
				block.push_back(i);

			block.push_back(lines[i]);
		}
		
		else if (lines[i] == "end" && !in_another_block)
		{
			*start = i;
			block.erase(block.end() - 1);
			break;
		}

		else if (lines[i + 1] == "end" && !in_another_block)
		{
			*start = i + 1;
			break;
		}
	}

	return block;
}

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

string Code::b_e_remove_space(string source)
{
	int i = 0;

	while (true)
	{
		if (source[i] == ' ' || source[i] == '\t') // \t = tab
			source.erase(i, 1);

		else
			break;
	}

	if (source != "")
		if (source[source.size() - 1] == ' ' || source[source.size() - 1] == '\t')
			source.erase(source.size() - 1);

	return source;
}

vector<string> Code::get_args(vector<string> args, vector<string> line, Variables vars, Line* lines, bool ignore_quotes)
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

				if (line[o] != "" && line[o][line[o].size() - 1] == '\"' && Code::b_e_remove_space(full) != "\"")
				{
					i = o;
					break;
				}
			}

			if (!ignore_quotes)
			{
				full.erase(0, 1);
				full.erase(full.size() - 2);
			}

			args_vec.push_back(full);
		}

		else if (line[i][0] == '*')
		{
			line[i].erase(0, 1);

			if (!vars.exist(line[i]))
			{
				Exception::_var_not_found(*lines, line[i]);
				lines->abort = true;
				break;
			}

			else if (i + 1 < line.size() && line[i + 1] == ":")
			{
				if (vars.get_type(line[i]) == "array")
				{
					if (i + 2 >= line.size())
					{
						Exception::_missing_index(*lines, line[i] + ' ' + line[i + 1]);
						lines->abort = true;
						break;
					}

					else
					{
						vector<string> value = { "_null_" };
						int i_line = 0;

						for (int o = i + 2; o < line.size(); o++)
						{
							value.push_back(line[o]);
							i_line++;
						}

						vector<string> index = Code::get_args(args, value, vars, lines, false);

						if (stoi(index[0]) >= vars.get_array_values(line[i]).size())
						{
							Exception::_array_size_overflow(*lines, line[i] + " " + line[i + 1] + " " + line[i + 2]);
							lines->abort = true;
							break;
						}

						else
							args_vec.push_back(vars.get_array_values(line[i])[stoi(index[0])]);
						
						i = i_line;
					}

					i += 2;
				}

				else if (vars.get_type(line[i]) == "string")
				{
					vector<string> value = { "_null_" };
					int i_line = 0;

					for (int o = i + 2; o < line.size(); o++)
					{
						value.push_back(line[o]);
						i_line++;
					}

					vector<string> index = Code::get_args(args, value, vars, lines, false);

					if (stoi(index[0]) >= vars.get_array_values(line[i])[0].size())
					{
						Exception::_array_size_overflow(*lines, line[i] + " " + line[i + 1] + " " + line[i + 2]);
						lines->abort = true;
						break;
					}
					
					else
					{
						string ch(1, vars.get_value(line[i])[stoi(index[0])]);

						args_vec.push_back(ch);
					}

					i = i_line;
				}

				i += 2;
			}

			else if (i + 1 < line.size() && line[i + 1] == "->")
			{
				if (i + 2 >= line.size())
				{
					Exception::_missing_attribute(*lines, line[i] + ' ' + line[i + 1]);
					lines->abort = true;
					break;
				}

				else if (line[i + 2] == "index")
					args_vec.push_back(to_string(vars.get_iterator_index(line[i])));

				else if (i + 2 < line.size() && line[i + 2] == "type")
					args_vec.push_back(vars.get_type(line[i]));

				else if (i + 2 < line.size() && vars.get_type(line[i]) == "string")
				{
					if (line[i + 2] == "size")
						args_vec.push_back(to_string(vars.get_value(line[i]).size()));

					else
					{
						Exception::_undefined_attribute(*lines, line[i + 2]);
						lines->abort = true;
						break;
					}
				}

				else if (i + 2 < line.size() && vars.get_type(line[i]) == "array")
				{
					if (line[i + 2] == "size")
						args_vec.push_back(to_string(vars.get_array_values(line[i]).size()));

					else if (line[i + 2] == "find")
					{
						vector<string> value = {"_null_"};
						int i_line = 0;

						for (int o = i + 3; o < line.size(); o++)
						{
							value.push_back(line[o]);
							i_line++;
						}

						value = Code::get_args(args, value, vars, lines, false);

						int index = vars.find_array_value(line[i], value[0]);

						args_vec.push_back(to_string(index));
						i = i_line;
						i++;
					}

					else
					{
						Exception::_undefined_attribute(*lines, line[i + 2]);
						lines->abort = true;
						break;
					}
				}
				
				else
				{
					Exception::_undefined_attribute(*lines, line[i + 2]);
					lines->abort = true;
					break;
				}

				i += 2;
			}

			else if (vars.get_type(line[i]) == "array")
			{
				vector<string> vals = vars.get_array_values(line[i]);
				string vals_str = "";

				for (int i = 0; i < vals.size(); i++)
					vals_str += vals[i] + ((i + 1 >= vals.size()) ? "" : "  |  ");

				vals_str = "[ " + vals_str + " ]";

				args_vec.push_back(vals_str);
			}

			else
				args_vec.push_back(vars.get_value(line[i]));
		}

		else if (line[i][0] == '%')
		{
			line[i].erase(0, 1);

			args_vec.push_back(args[stoi(line[i]) - 1]);
		}

		else if (line[i] == "+")
		{
			vector<string> aux = { "_null_" };

			for (int o = i + 1; o < line.size(); o++)
			{
				aux.push_back(line[o]);
				i = o;
			}

			args_vec[args_vec.size() - 1] = args_vec[args_vec.size() - 1] + Code::get_args(args, aux, vars, lines, false)[0];
			i++;
		}

		else
			args_vec.push_back(line[i]);
	}

	return args_vec;
}