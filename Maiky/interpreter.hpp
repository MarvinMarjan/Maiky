#pragma once

#include <fstream>
#include <string>
#include <vector>

class Interpreter
{
public:
	Interpreter();

	void open(std::string path);
	std::vector<std::string> read();

	bool could_open();

private:
	std::fstream file;
};