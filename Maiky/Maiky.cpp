#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "interpreter.hpp"
#include "bootstrap.hpp"
#include "condition.hpp"
#include "exception.hpp"
#include "utilities.hpp"
#include "variables.hpp"
#include "buffer.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

void exec(int argc, vector<string> args, Line& lines, Variables ls_vars, Line& last_lines)
{
	Variables vars = ls_vars;
	Buffer buffer;

	bool cond_res = true;

	for (int i = 0; i < lines.get_size(); i++)
	{
		vector<string> line = Utils::split_string(lines[i]);

		if (lines.abort)
			break;

		if (line.size() == 0)
		{
			lines.update();
			continue;
		}

		if (line[0] == "print")
		{
			line = Code::get_args(args, line, vars, &lines);

			if (!lines.abort)
				for (string i : line)
					buffer << i;
		}

		else if (line[0] == "input")
		{
			line = Code::get_args(args, line, vars, &lines);

			if (vars.exist(line[1]))
			{
				string buff;

				getline(cin, buff);

				vars.edit_var(line[1], line[0], buff);
			}

			else
			{
				Exception::_var_not_found(lines, line[1]);
				lines.abort = true;
			}
		}

		else if (line[0] == "def") 
		{
			line = Code::get_args(args, line, vars, &lines);

			if (line[1] == "null")
				line.push_back("null");

			if (!vars.valid_type(line[1]))
			{
				Exception::_undefined_type(lines, line[1]);
				lines.abort = true;
			}

			if (!lines.abort)
				vars.add_var({line[0], {line[1], line[2]}});
		}

		else if (line[0] == "mod")
		{
			line = Code::get_args(args, line, vars, &lines);

			if (vars.exist(line[0]))
			{
				if (vars.valid_type(line[1]))
					vars.edit_var(line[0], line[1], line[2]);

				else
				{
					Exception::_undefined_type(lines, line[1]);
					lines.abort = true;
				}
			}

			else
			{
				Exception::_var_not_found(lines, line[1]);
				lines.abort = true;
			}
		}
		
		else if (line[0] == "if")
		{
			line = Code::get_args(args, line, vars, &lines);

			line.erase(line.end() - 1);

			vector<vector<string>> conds = Condition::get_condition(line);
			
			i++;
			lines.update();

			Line block(Code::get_code_block(lines, &i), lines.get_current_line(), false);
			cond_res = Condition::check_all(conds);

			if (cond_res)
				exec(argc, args, block, vars, lines);
		}

		else if (line[0] == "else")
		{
			i++;
			lines.update();

			Line block(Code::get_code_block(lines, &i), lines.get_current_line(), false);
			
			if (!cond_res)
				exec(argc, args, block, vars, lines);
		}

		else
		{
			Exception::_cmd_not_found(lines, line[0]);
			lines.abort = true;
		}

		//cout << "current: " << lines.get_current_line() << endl;
		//cout << "true: " << lines.get_true_line() << endl << endl;

		last_lines.update();
		lines.update();
	}
}
 
int main(int argc, char* argv[])
{
	string source_path = (argc < 2) ? Bootstrap::check_runtime_config()["path"] : argv[1];
	vector<string> program_args;

	if (argc < 2)
		program_args = Utils::split_string(Bootstrap::check_runtime_config()["args"]);

	else
		for (int i = 2; argv[i] != nullptr; i++)
			program_args.push_back(argv[i]);

	Interpreter source;
	source.open(source_path);

	if (!source.could_open())
		Exception::_file_not_found(source_path);

	else
	{
		Line lines(source.read(), 0, true);
		Line aux({}, 0, false);
	
		for (int i = 0; i < lines.get_size(); i++)
			lines.set_lines_index(Code::b_e_remove_space(lines[i]), i);

		exec(argc, program_args, lines, Variables(), aux);
	}

	cin.get();
}