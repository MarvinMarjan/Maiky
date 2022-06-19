#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "interpreter.hpp"
#include "bootstrap.hpp"
#include "exception.hpp"
#include "utilities.hpp"
#include "buffer.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

void exec(Line& lines)
{
	Buffer buffer;

	for (int i = 0; i < lines.get_size(); i++)
	{
		vector<string> line = Utils::split_string(lines[i]);

		if (lines.abort)
			break;

		if (line[0] == "print")
		{
			line = Code::get_args(line);

			for (string i : line)
				buffer << i ;
		}

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

	Line lines(source.read());
	
	for (int i = 0; i < lines.get_size(); i++)
		lines.set_lines_index(Code::remove_start_space(lines[i]), i);

	exec(lines);
}