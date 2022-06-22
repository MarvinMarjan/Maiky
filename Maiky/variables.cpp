#include <string>
#include <vector>
#include <map>

#include "variables.hpp"

using namespace std;

bool Variables::valid_type(string type)
{
	if (type == "string")
		return true;

	else if (type == "int")
		return true;

	else if (type == "float")
		return true;

	else if (type == "bool")
		return true;

	else if (type == "null")
		return true;

	else
		return false;
}

void Variables::add_var(pair<string, vector<string>> var)
{
	this->vars.insert(var);
}

void Variables::edit_var(string var_name, string new_type, string new_value)
{
	this->vars[var_name][1] = new_value;
	this->vars[var_name][0] = new_type;
}

void Variables::rmv_var(string var_name)
{
	this->vars.erase(var_name);
}

string Variables::get_type(string var_name)
{
	return this->vars[var_name][0];
}

string Variables::get_value(string var_name)
{
	return this->vars[var_name][1];
}

bool Variables::exist(string var_name)
{
	for (auto i : this->vars)
		if (i.first == var_name)
			return true;
	
	return false;
}