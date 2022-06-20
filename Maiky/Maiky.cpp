#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "interpreter.hpp"
#include "bootstrap.hpp"
#include "exception.hpp"
#include "utilities.hpp"
#include "variables.hpp"
#include "buffer.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

void exec(int argc, char* argv[], Line& lines)
{
	Variables vars;
	Buffer buffer;

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
			line = Code::get_args(argv, line, vars, &lines);

			if (!lines.abort)
				for (string i : line)
					buffer << i;
		}

		else if (line[0] == "def") 
		{
			line = Code::get_args(argv, line, vars, &lines);

			if (!lines.abort)
				vars.add_var({line[0], {line[1], line[2]}});
		}

		else
			Exception::_cmd_not_found(lines, line[0]);

		lines.update();
	}
}
 
int main(int argc, char* argv[])
{
	string source_path = (argv[1] == nullptr) ? Bootstrap::check_runtime_config()["path"] : argv[1];

	Interpreter source;
	source.open(source_path);

	if (!source.could_open())
		Exception::_file_not_found(source_path);

	else
	{
		Line lines(source.read());
	
		for (int i = 0; i < lines.get_size(); i++)
			lines.set_lines_index(Code::remove_start_space(lines[i]), i);

		exec(argc, argv, lines);
	}

}