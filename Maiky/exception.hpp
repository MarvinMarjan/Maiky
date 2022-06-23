#pragma once

#include <string>

#include "line.hpp"

class Exception
{
public:
	static void _initial_code_block_not_detected(Line& lines);

	static void _file_not_found(std::string path);
	static void _cmd_not_found(Line lines, std::string cmd_name);
	static void _var_not_found(Line& line, std::string var_name);

	static void _existent_var_def(std::string var_name, Line line);

	static void _undefined_type(Line line, std::string type_name);
	static void _undefined_attribute(Line& line, std::string attribute);

	static void _missing_attribute(Line& line, std::string _where);
	static void _missing_index(Line& line, std::string _where);

	static void _array_size_overflow(Line& line, std::string _where);
};