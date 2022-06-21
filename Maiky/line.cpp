#include <vector>
#include <string>

#include "exception.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

Line::Line(vector<string> source, int last_i, bool init)
{
	this->lines = source;
	this->current_line = 0;
	this->true_line = last_i;

	if (init)
	{
		if (this->lines[0] == "start" && this->lines[this->lines.size() - 1] == "end")
		{
			this->lines = Code::get_code_block(*this, 1);
			this->abort = false;
		}

		else
		{
			Exception::_initial_code_block_not_detected(*this);
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