#pragma once

#include <string>
#include <vector>

class Condition
{
public:
	static bool check(std::vector<std::string> cond);
	static bool check_all(std::vector<std::vector<std::string>> conds);

	static std::vector<std::vector<std::string>> get_condition(std::vector<std::string> line);
};