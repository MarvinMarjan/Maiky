#include <direct.h>
#include <dirent.h>
#include <string>
#include <vector>

#include "dir_sys.hpp"

using namespace std;

vector<string> Dir_sys::get_dir_list(string path)
{
	DIR* dir = opendir(path.c_str());
	vector<string> list;

	struct dirent* ent;

	while ((ent = readdir(dir)) != NULL)
		list.push_back(ent->d_name);

	return list;
}

void Dir_sys::create_dir(string d_path)
{
	int _trash = _mkdir(d_path.c_str());
}

void Dir_sys::remove_dir(string d_path)
{
	int _trash = _rmdir(d_path.c_str());
}

bool Dir_sys::dir_exist(string d_path)
{
	DIR* dir = opendir(d_path.c_str());

	if (!dir)
		return false;

	else
		return true;
}