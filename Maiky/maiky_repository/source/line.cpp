#include <vector>
#include <string>

#include "line.hpp"

using namespace std;

Line::Line(vector<string> source)
{
	this->lines = source;
	this->current_line = 1;
}

string Line::operator[](int index)
{
	return this->lines[index];
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