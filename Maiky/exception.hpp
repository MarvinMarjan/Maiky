#pragma once

#include <string>

#include "line.hpp"

class Exception
{
public:
	static void _initial_code_block_not_detected(Line lines, int highlight);
	static void _file_not_found(std::string path);
};