#pragma once

#include <string>
#include <vector>
#include <map>

class Function
{
public:
	Function(std::vector<std::string> source);
	Function();

	void set_args_val(std::string func_name, std::vector<std::string> args_val);
	void set_return(std::string func_name, std::vector<std::string> ret);

	void add_func(std::vector<std::pair<std::string, std::vector<std::string>>> func);

	std::vector<std::string> get_return_value(std::string func_name);
	std::pair<std::string, std::vector<std::string>> get_func(std::string func_name);
	std::pair<std::string, std::vector<std::string>> get_args(std::string func_name);

	bool func_exist(std::string func_name);

private:
	/* 
	   0: {func_name: [block]} -> function name and it's block
	   1: {args_name: [num1, num2]} -> args name
	   2: {args_val: [3, 5]} -> args value
	   3: {return: return_value} -> if the function returns a value

	   [
		  [ 
		     {"main": ["block"]}, 
			 {"args": ["1", false]}
		  ],

		  [
		     {"printer": ["block"]},
			 {"args": ["str"]}
			 {"args_val": ["hello, world"]}
		  ],

		  [
		     {"get_num": [block]},
			 {"args": []}
			 {"args_val": []},
			 {"return": 5}
		  ]
	   ]
	*/

	std::vector<std::vector<std::pair<std::string, std::vector<std::string>>>> funcs;
};