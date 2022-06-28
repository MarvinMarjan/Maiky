#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utilities.hpp"
#include "function.hpp"
#include "code.hpp"
#include "line.hpp"

using namespace std;

Function::Function() {}

Function::Function(vector<string> source)
{
	Line lines(source, 0, false);

	for (int i = 0; i < source.size(); i++)
	{
		vector<string> line = Utils::split_string(source[i]);

		if (!line.size())
			continue;

		if (line[0] == "function")
		{
			string name = line[1];
			vector<string> args;

			for (int p = 2; p < line.size(); p++)
				args.push_back(line[p]);

			int o = i + 2;

			vector<string> block = Code::get_code_block(lines, &o);

			for (int p = 0; p < block.size(); p++)
				block[p] = Code::b_e_remove_space(block[p]);

			this->add_func({
				{ name, block },
				{ "args", args },
				{ "args_val", { "_null_" } },
				{ "return", { "_null_" } }
			});

			i = o;
		}
	}
}

void Function::set_args_val(string func_name, vector<string> args_val)
{
	for (int i = 0; i < this->funcs.size(); i++)
		if (this->funcs[i][0].first == func_name)
			this->funcs[i][2].second = args_val;
}

void Function::set_return(string func_name, vector<string> ret)
{
	for (int i = 0; i < this->funcs.size(); i++)
		if (this->funcs[i][0].first == func_name)
			this->funcs[i][3].second = ret;
}

void Function::add_func(vector<pair<string, vector<string>>> func)
{
	this->funcs.push_back(func);
}

vector<string> Function::get_return_value(string func_name)
{
	for (int i = 0; i < this->funcs.size(); i++)
		if (this->funcs[i][0].first == func_name)
			return this->funcs[i][3].second;
}

pair<string, vector<string>> Function::get_func(string func_name)
{
	for (int i = 0; i < this->funcs.size(); i++)
		if (this->funcs[i][0].first == func_name)
			return this->funcs[i][0];
	
	return { "_null_", {"_null_"} };
}

pair<string, vector<string>> Function::get_args(string func_name)
{
	for (int i = 0; i < this->funcs.size(); i++)
		if (this->funcs[i][0].first == func_name)
			return this->funcs[i][1];

	return { "_null_", {"_null_"} };
}

bool Function::func_exist(string func_name)
{
	for (int i = 0; i < this->funcs.size(); i++)
		if (this->funcs[i][0].first == func_name)
			return true;
	
	return false;
}