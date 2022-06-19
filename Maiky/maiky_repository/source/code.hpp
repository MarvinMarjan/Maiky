#pragma once

class Code
{
public:
	static std::vector<std::string> get_code_block(Line lines, int start);
	static std::string remove_start_space(std::string source);
};