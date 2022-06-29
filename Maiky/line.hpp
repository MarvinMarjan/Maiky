#pragma once

#include <string>
#include <vector>

#include "function.hpp"

class Line
{
public:
	Line(std::vector<std::string> source, int last_i, bool init, Function* func = nullptr);

	std::string operator[](int index);
	void operator=(std::vector<std::string> lines);

	void set_lines(std::vector<std::string> lines);
	void set_lines_index(std::string value, int index);

	int get_size();
	int get_current_line();
	int get_true_line();

	void update();

	bool abort;

private:
	std::vector<std::string> lines;

	int current_line;
	int true_line;
};