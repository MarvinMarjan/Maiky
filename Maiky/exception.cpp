#include <iostream>
#include <string>

#include "exception.hpp"
#include "line.hpp"

using namespace std;

void Exception::_initial_code_block_not_detected(Line lines, int highlight)
{
	cout << "ERROR (line " << lines.get_current_line() + 1 << ") : no initial code block detected:\n" << lines[lines.get_current_line()] << endl;

	for (int i = 0; i < highlight; i++)
		cout << " ";

	cout << "^" << endl;
}

void Exception::_file_not_found(string path)
{
	cout << "ERROR: file " << '\"' + path + '\"' << " does not exist" << endl;
}