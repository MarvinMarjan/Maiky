#pragma once

#include <vector>
#include <string>

class Utils
{
public:
	static std::vector<std::string> split_string(std::string source);
	static std::string concat_string(std::vector<std::string> source);
	static int find_val_array(std::string val, std::vector<std::string> target);
	static std::vector<std::string> erase(std::vector<std::string> target, int start, int end);
};