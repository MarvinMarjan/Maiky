#pragma once

#include <string>
#include <vector>

class Dir_sys
{
public:
	static std::vector<std::string> get_dir_list(std::string path);

	static void create_dir(std::string d_path);
	static void remove_dir(std::string d_path);

	static bool dir_exist(std::string d_path);
};