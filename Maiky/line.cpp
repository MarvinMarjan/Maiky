#include <vector>
#include <string>

#include "exception.hpp"
#include "utilities.hpp"
#include "function.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

Line::Line(vector<string> source, int last_i, bool init, Function func)
{
	this->lines = source;
	this->current_line = (init) ? Utils::find_val_array("function main", source) : 0;
	this->true_line = last_i;

	if (init)
	{
		if (func.func_exist("main"))
		{
			this->lines = func.get_func("main").second;
			this->abort = false;
		}
		

		else
		{
			Exception::_main_function_not_found();
			this->abort = true;
		}
	}

	else
		this->abort = false;
}

string Line::operator[](int index)
{
	return this->lines[index];
}

void Line::operator=(vector<string> lines) 
{
	this->set_lines(lines);
}

void Line::set_lines(vector<string> lines)
{
	this->lines = lines;
}

void Line::set_lines_index(string value, int index)
{
	this->lines[index] = value;
}

int Line::get_size()
{
	int size = 0;

	for (string i : this->lines)
		size++;

	return size;
}

int Line::get_current_line()
{
	return this->current_line;
}

int Line::get_true_line()
{
	return this->true_line;
}

void Line::update()
{
	this->current_line += 1;
}