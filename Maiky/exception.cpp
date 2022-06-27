#include <iostream>
#include <string>

#include "exception.hpp"
#include "line.hpp"

using namespace std;

void Exception::_initial_code_block_not_detected(Line& lines)
{
	cout << "ERROR (line " << lines.get_current_line() + 2 << 
		") : no initial code block detected:\n\n" << lines[lines.get_current_line()] << endl << endl;
}



void Exception::_file_not_found(string path)
{
	cout << "ERROR: file " << '\"' + path + '\"' << " does not exist" << endl << endl;
}

void Exception::_cmd_not_found(Line lines, string cmd_name)
{
	cout << "ERROR (line " << lines.get_current_line() + 2 << "): command " << 
		'\"' + cmd_name + '\"' << " is not a command:\n\n" << lines[lines.get_current_line()] << endl << endl;
}

void Exception::_var_not_found(Line& line, string var_name)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): variable " << '\"' + var_name + '\"' << " does not exist:\n\n" << line[line.get_current_line()] << endl << endl;
}



void Exception::_existent_var_def(string var_name, Line line)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): definition of an existing variable: " << '\"' + var_name + '\"' << ":\n\n" << line[line.get_current_line()] << endl << endl;

}



void Exception::_undefined_type(Line line, string type_name)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): type " << '\"' + type_name + '\"' << " is undefined:\n\n" << line[line.get_current_line()] << endl << endl;
}

void Exception::_undefined_attribute(Line& line, string attribute)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): the attribute: " << '\"' + attribute + '\"' << " is undefined:\n\n" << line[line.get_current_line()] << endl;
}



void Exception::_missing_argument(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): missing argument: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;

}

void Exception::_missing_attribute(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): missing argument: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;
}

void Exception::_missing_index(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): the index is missing: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;
}



void Exception::_array_size_overflow(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): an array overflow happened: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;
}



void Exception::_could_not_open_file(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): couldn't open file: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;
}

void Exception::_could_not_open_dir(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): couldn't open directory: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;
}

void Exception::_wrong_parameter_type(Line& line, string _where)
{
	cout << "ERROR (line " << line.get_current_line() + line.get_true_line() + 2 << "): wrong parameter type: " << '\"' + _where + '\"' << "\n\n" << line[line.get_current_line()] << endl << endl;
}