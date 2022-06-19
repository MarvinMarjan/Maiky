#pragma once

#include <string>
#include <vector>

class Line
{
public:
	Line(std::vector<std::string> source);

	std::string operator[](int index);
	void operator=(std::vector<std::string> lines);

	void set_lines(std::vector<std::string> lines);
	void set_lines_index(std::string value, int index);

	int get_size();
	int get_current_line();

	void update();

	bool abort;

private:
	std::vector<std::string> lines;

	int current_line;
};