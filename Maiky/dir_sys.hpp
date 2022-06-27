#pragma once

#include <string>
#include <vector>

class Dir_sys
{
public:
	static void create_dir(std::string d_path);
	static void remove_dir(std::string d_path);

	static bool dir_exist(std::string d_path);
};