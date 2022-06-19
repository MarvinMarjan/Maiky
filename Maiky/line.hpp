#pragma once

class Line
{
public:
	Line(std::vector<std::string> source);

	std::string operator[](int index);

	int get_size();
	int get_current_line();

	void update();

private:
	std::vector<std::string> lines;

	int current_line;
};