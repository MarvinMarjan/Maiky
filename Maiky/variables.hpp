#pragma once

#include <string>
#include <vector>
#include <map>

class Variables
{
public:
	bool valid_type(std::string type);

	void add_var(std::pair<std::string, std::vector<std::string>> var);
	void edit_var(std::string var_name, std::string new_type, std::string new_value);

	std::string get_type(std::string var_name);
	std::string get_value(std::string var_name);

	bool exist(std::string var_name);

private:
	std::map<std::string, std::vector<std::string>> vars;
};