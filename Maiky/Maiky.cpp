// Maiky_info.hpp: #define _VERSION "0.0.3 (BETA)"

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
#include "file_sys.hpp"
#include "dir_sys.hpp"
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
		{
			cin.get();
			break;
		}

		if (line.size() == 0)
		{
			lines.update();
			continue;
		}

		if (line[0] == "pause")
			cin.get();

		else if (line[0][0] == '*')
		{
			line[0].erase(0, 1);

			if (!vars.exist(line[0]))
			{
				Exception::_var_not_found(lines, line[0]);
				lines.abort = true;
			}

			else if (1 < line.size() && line[1] == "->")
			{
				if (vars.get_type(line[0]) == "array")
				{
					if (2 < line.size() && line[2] == "add")
					{
						vector<string> val = Code::get_args(args, { "_null_", line[3] }, vars, &lines, true);

						vars.add_array_value(line[0], val[0]);
					}

					else if (2 < line.size() && line[2] == "del")
						vars.rmv_array_value(line[0], stoi(line[3]));
				}
			}
		}

		else if (line[0] == "print")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			line = Code::get_args(args, line, vars, &lines, false);

			if (!lines.abort)
				for (string i : line)
					buffer << i;
		}

		else if (line[0] == "input")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

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
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			vector<string> quotes_line = Code::get_args(args, line, vars, &lines, false);
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
				{
					if (line.size() < 3)
						vars.add_var({ line[0], {line[1], ""} });

					else
						vars.add_var({ line[0], {line[1], line[2]} });
				}

				scope_vars.push_back(line[0]);
			}
		}

		else if (line[0] == "mod")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			line = Code::get_args(args, line, vars, &lines, false);

			if (!lines.abort)
			{
				if (vars.exist(line[0]))
				{
					if (vars.valid_type(line[1]) || line[1] == ":")
					{
						if (vars.get_type(line[0]) == "array")
						{
							if (line[1] == ":")
								vars.edit_array_value(line[0], line[4], stoi(line[2]));

							else
								vars.edit_var(line[0], line[1], line[2]);
						}

						else
							vars.edit_var(line[0], line[1], line[2]);
					}

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
		}

		else if (line[0] == "if")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

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
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

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
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

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

		else if (line[0] == "for")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			line = Code::get_args(args, line, vars, &lines, false);
			line.erase(line.end() - 1);

			vars.add_iterator(line[0], "null", -1);

			i++;
			lines.update();

			Line block(Code::get_code_block(lines, &i), lines.get_current_line(), false);

			if (line[1] == "in")
			{
				for (int o = 0; o < vars.get_array_values(line[2]).size(); o++)
				{
					vars.edit_iterator(line[0], vars.get_array_values(line[2])[o], o);

					exec(argc, args, block, vars, lines);
				}
			}
		}

		else if (line[0] == "mfile")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			line = Code::get_args(args, line, vars, &lines, false);

			File_sys::create_file(line[0]);
		}

		else if (line[0] == "rmfile")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			line = Code::get_args(args, line, vars, &lines, false);

			if (File_sys::file_exist(line[0]))
				File_sys::remove_file(line[0]);

			else
				Exception::_could_not_open_file(lines, line[0]);
		}

		else if (line[0] == "mdir")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			else
			{
				line = Code::get_args(args, line, vars, &lines, false);

				Dir_sys::create_dir(line[0]);
			}
		}

		else if (line[0] == "rmdir")
		{
			if (line.size() < 2)
			{
				Exception::_missing_argument(lines, line[0]);
				lines.abort = true;
			}

			else
			{
				line = Code::get_args(args, line, vars, &lines, false);

				if (Dir_sys::dir_exist(line[0]))
					Dir_sys::remove_dir(line[0]);

				else
				{
					Exception::_could_not_open_dir(lines, line[0]);
					lines.abort = true;
				}
			}
		}

		else if (line[0] == "read")
		{
			line = Code::get_args(args, line, vars, &lines, false);

			if (File_sys::file_exist(line[0]))
			{
				if (vars.exist(line[1]))
				{
					if (vars.get_type(line[1]) == "array")
						vars.edit_array_var(line[1], File_sys::read_file(line[0]));

					else if (vars.get_type(line[1]) == "string")
					{
						string content = "";

						for (string str : File_sys::read_file(line[0]))
							content += str + '\n';

						vars.edit_var(line[1], "string", content);
					}

					else
					{
						Exception::_wrong_parameter_type(lines, line[1]);
						lines.abort = true;
					}
				}

				else
				{
					Exception::_var_not_found(lines, line[1]);
					lines.abort = true;
				}
			}

			else
			{
				Exception::_could_not_open_file(lines, line[0]);
				lines.abort = true;
			}
		}

		else if (line[0] == "write")
		{
			line = Code::get_args(args, line, vars, &lines, false);

			if (File_sys::file_exist(line[0]))
				File_sys::write_file(line[0], line[1]);

			else
			{
				Exception::_could_not_open_file(lines, line[0]);
				lines.abort = true;
			}
		}

		else
		{
			Exception::_cmd_not_found(lines, line[0]);
			lines.abort = true;
		}

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
	{
		program_args = Utils::split_string(Bootstrap::check_runtime_config()["args"]);
		program_args = Bootstrap::check_program_args(program_args);
	}

	else
		program_args = Bootstrap::check_program_args(argc, argv);

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

	//cin.get();
}