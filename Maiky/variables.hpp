#pragma once

#include <string>
#include <vector>
#include <map>

class Variables
{
public:
	bool valid_type(std::string type);

	void add_array_value(std::string arr_name, std::string arr_value);
	void add_array(std::string var_name, std::vector<std::string> vals, std::string var_type);
	void add_var(std::pair<std::string, std::vector<std::string>> var);
	void add_iterator(std::string var_name, std::string value, int index);

	void edit_array_value(std::string var_name, std::string new_value, int index);
	void edit_array_var(std::string var_name, std::vector<std::string> new_array);
	void edit_var(std::string var_name, std::string new_type, std::string new_value);
	void edit_iterator(std::string var_name, std::string new_value, int index);

	void rmv_array_value(std::string var_name, int index);
	void rmv_var(std::string var_name);

	int find_array_value(std::string var_name, std::string value);

	std::string define_type(std::string value);
	std::string get_type(std::string var_name);
	std::string get_value(std::string var_name);
	std::vector<std::string> get_array_values(std::string var_name);
	int get_iterator_index(std::string var_name);

	std::vector<std::string> get_var_list();

	bool exist(std::string var_name);

private:
	std::map<std::string, std::vector<std::string>> vars;
};