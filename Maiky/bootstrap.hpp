#pragma once

#include <string>
#include <map>

class Bootstrap
{
public:
	static std::map<std::string, std::string> check_runtime_config();
};