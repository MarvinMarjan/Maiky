#pragma once

#include <string>
#include <map>

class Bootstrap
{
public:
	static std::map<std::string, std::string> check_runtime_config();

	static std::vector<std::string> check_program_args(int argc, char* argv[]);
	static std::vector<std::string> check_program_args(std::vector<std::string> args);
};