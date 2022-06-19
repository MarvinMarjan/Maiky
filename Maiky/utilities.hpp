#pragma once

#include <vector>
#include <string>

class Utils
{
public:
	static std::vector<std::string> split_string(std::string source);
	static std::string concat_string(std::vector<std::string> source);
};