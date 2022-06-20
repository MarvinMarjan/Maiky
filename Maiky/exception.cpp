#include <iostream>
#include <string>

#include "exception.hpp"
#include "line.hpp"

using namespace std;

void Exception::_initial_code_block_not_detected(Line lines)
{
	cout << "ERROR (line " << lines.get_current_line() + 1 << 
		") : no initial code block detected:\n\n" << lines[lines.get_current_line()] << endl;
}

void Exception::_file_not_found(string path)
{
	cout << "ERROR: file " << '\"' + path + '\"' << " does not exist" << endl;
}

void Exception::_cmd_not_found(Line lines, string cmd_name)
{
	cout << "ERROR (line " << lines.get_current_line() + 1 << "): command " << 
		'\"' + cmd_name + '\"' << " is not a command:\n\n" << lines[lines.get_current_line()] << endl;
}

void Exception::_var_not_found(Line& line, string var_name)
{
	cout << "ERROR (line " << line.get_current_line() + 1 << "): variable " << '\"' + var_name + '\"' << " does not exist:\n\n" << line[line.get_current_line()] << endl;
}