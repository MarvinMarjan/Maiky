#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "interpreter.hpp"
#include "bootstrap.hpp"
#include "exception.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string source_path = (argv[1] == nullptr) ? Bootstrap::check_runtime_config()["path"] : argv[1];

	Interpreter source;
	source.open(source_path);

	Line lines(source.read());

	for (int i = 0; i < lines.get_size(); i++)
	{
		if (lines[0] != "start")
			Exception::_initial_code_block_not_detected(lines, 0);

		lines.update();
	}
}