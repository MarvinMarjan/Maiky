#pragma once

class Interpreter
{
public:
	Interpreter();

	void open(std::string path);
	std::vector<std::string> read();

private:
	std::fstream file;
};