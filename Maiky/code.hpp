#pragma once

#include <string>
#include <vector>
#include <map>

#include "variables.hpp"
#include "line.hpp"

class Code
{
public:
	static std::vector<std::string> get_code_block(Line& lines, int* start);
	static std::vector<std::string> get_code_block(Line& lines, int start);

	static std::string b_e_remove_space(std::string source);
	static std::vector<std::string> get_args(std::vector<std::string> args, std::vector<std::string> line, Variables vars, Line* lines, bool ignore_quotes, Function* func = nullptr);
};