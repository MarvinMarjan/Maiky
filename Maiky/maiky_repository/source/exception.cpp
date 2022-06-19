#include <iostream>
#include <string>
#include <vector>

#include "exception.hpp"
#include "line.hpp"

using namespace std;

void Exception::_initial_code_block_not_detected(string lines, int highlight)
{
	cout << "no initial code block detected:\n" << lines[lines.get_current_line()] << endl;

	for (int i = 0; i < highlight; i++)
		cout << " ";

	cout << "^" << endl;
}