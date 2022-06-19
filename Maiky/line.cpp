#include <vector>
#include <string>

#include "exception.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

Line::Line(vector<string> source)
{
	this->lines = source;
	this->current_line = 0;

	if (this->lines[0] == "start")
	{
		this->lines = Code::get_code_block(*this, 1);
		this->abort = false;
	}

	else
	{
		Exception::_initial_code_block_not_detected(lines, 0);
		this->abort = true;
	}
		
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

void Line::update()
{
	this->current_line += 1;
}