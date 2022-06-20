#include <string>
#include <vector>
#include <map>

#include "variables.hpp"

using namespace std;

void Variables::add_var(pair<string, vector<string>> var)
{
	this->vars.insert(var);
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