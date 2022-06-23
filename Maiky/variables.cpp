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

	else if (type == "array")
		return true;

	else if (type == "null")
		return true;

	else if (type == "iterator")
		return true;

	else
		return false;
}

void Variables::add_array_value(string arr_name, string arr_value)
{
	this->vars[arr_name].push_back(arr_value);
}

void Variables::add_array(string var_name, vector<string> vals, string var_type)
{
	this->vars.insert({ var_name, {var_type} });

	for (string val : vals)
		this->vars[var_name].push_back(val);
}

void Variables::add_var(pair<string, vector<string>> var)
{
	this->vars.insert(var);
}

void Variables::add_iterator(string var_name, string value, int index)
{
	this->vars.insert({ var_name, {"iterator", value, to_string(index)}});
}

void Variables::edit_array_value(string var_name, string new_value, int index)
{
	this->vars[var_name][index + 1] = new_value;
}

void Variables::edit_var(string var_name, string new_type, string new_value)
{
	this->vars[var_name][0] = new_type;
	this->vars[var_name][1] = new_value;
}

void Variables::edit_iterator(string var_name, string new_value, int index)
{
	this->vars[var_name][1] = new_value;
	this->vars[var_name][2] = to_string(index);
}

void Variables::rmv_array_value(string var_name, int index)
{
	vector<string>::iterator itr = find(this->vars[var_name].begin(), this->vars[var_name].end(), 
										this->vars[var_name][index + 1]);

	this->vars[var_name].erase(itr);
}

void Variables::rmv_var(string var_name)
{
	this->vars.erase(var_name);
}

int Variables::find_array_value(string var_name, string value)
{
	for (int i = 1; i < this->vars[var_name].size(); i++)
		if (this->vars[var_name][i] == value)
			return i - 1;

	return -1;
}

string Variables::get_type(string var_name)
{
	return this->vars[var_name][0];
}

string Variables::get_value(string var_name)
{
	return this->vars[var_name][1];
}

vector<string> Variables::get_array_values(string var_name)
{
	vector<string> vals;

	for (int i = 1; i < this->vars[var_name].size(); i++)
		vals.push_back(this->vars[var_name][i]);
	
	return vals;
}

int Variables::get_iterator_index(string var_name)
{
	return stoi(this->vars[var_name][2]);
}

bool Variables::exist(string var_name)
{
	for (auto i : this->vars)
		if (i.first == var_name)
			return true;
	
	return false;
}