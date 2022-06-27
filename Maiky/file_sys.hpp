#pragma once

#include <string>
#include <vector>

class File_sys
{
public:
	static void create_file(std::string f_path);
	static void remove_file(std::string f_path);

	static std::vector<std::string> read_file(std::string f_path);
	static void write_file(std::string f_path, std::string content);

	static bool file_exist(std::string f_path);

	static _off_t get_size(std::string f_path);

	static std::string get_type(std::string f_path);
};