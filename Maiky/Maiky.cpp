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

void exec(int argc, vector<string> args, Line& lines, Variables &vars, Line& last_lines)
{
	vector<string> scope_vars;
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

		if (line[0][0] == '*')
		{
			line[0].erase(0, 1);

			if (!vars.exist(line[0]))
			{
				Exception::_var_not_found(lines, line[0]);
				lines.abort = true;
			}

			else if (1 < line.size() && line[1] == "->")
			{
				if (2 < line.size() && line[2] == "add")
				{
					vector<string> val = Code::get_args(args, { "_null_", line[3] }, vars, &lines, true);

					vars.add_array_value(line[0], val[0]);
				}
			}
		}

		else if (line[0] == "print")
		{
			line = Code::get_args(args, line, vars, &lines, false);

			if (!lines.abort)
				for (string i : line)
					buffer << i;
		}

		else if (line[0] == "input")
		{
			line = Code::get_args(args, line, vars, &lines, false);

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
			vector<string> quotes_line = Code::get_args(args, line, vars, &lines, true);
			line = Code::get_args(args, line, vars, &lines, false);

			if (line[1] == "null")
				line.push_back("null");

			if (vars.exist(line[0]))
			{
				Exception::_existent_var_def(line[0], lines);
				lines.abort = true;
			}

			if (!vars.valid_type(line[1]))
			{
				Exception::_undefined_type(lines, line[1]);
				lines.abort = true;
			}

			if (!lines.abort)
			{
				if (line[1] == "array")
				{
					vector<string> vals;

					for (int o = 2; o < quotes_line.size(); o++)
						vals.push_back(quotes_line[o]);

					vars.add_array(quotes_line[0], vals, quotes_line[1]);
				}

				else
					vars.add_var({line[0], {line[1], line[2]}});

				scope_vars.push_back(line[0]);
			}
		}

		else if (line[0] == "mod")
		{
			line = Code::get_args(args, line, vars, &lines, false);

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
			line = Code::get_args(args, line, vars, &lines, false);

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

		else if (line[0] == "elif")
		{
			line = Code::get_args(args, line, vars, &lines, false);

			line.erase(line.end() - 1);

			vector<vector<string>> conds = Condition::get_condition(line);

			i++;
			lines.update();

			Line block(Code::get_code_block(lines, &i), lines.get_current_line(), false);

			if (!cond_res)
			{
				cond_res = Condition::check_all(conds);

				if (cond_res)
					exec(argc, args, block, vars, lines);
			}
		}

		else if (line[0] == "while")
		{
			Line cond_line = lines;

			line = Code::get_args(args, line, vars, &cond_line, false);
			line.erase(line.end() - 1);

			vector<vector<string>> conds = Condition::get_condition(line);
			
			int cond_index = i;

			i++;
			lines.update();

			Line block(Code::get_code_block(lines, &i), lines.get_current_line(), false);
			
			cond_res = Condition::check_all(conds);

			while (cond_res)
			{
				exec(argc, args, block, vars, lines);
				
				line = Utils::split_string(cond_line[cond_index]);
				line = Code::get_args(args, line, vars, &cond_line, false);

				line.erase(line.end() - 1);
				conds = Condition::get_condition(line);

				cond_res = Condition::check_all(conds);
			}

			if (!cond_res)
				i++;
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

	for (string i : scope_vars)
		vars.rmv_var(i);
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

		Variables vars;

		exec(argc, program_args, lines, vars, aux);
	}

	cin.get();
}