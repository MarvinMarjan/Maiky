#include <sys/stat.h>
#include <fstream>
#include <string>
#include <vector>

#include "file_sys.hpp"
#include "dir_sys.hpp"

using namespace std;

void File_sys::create_file(string f_path)
{
	fstream file;
	file.open(f_path, ios::out);

	file.close();
}

void File_sys::remove_file(string f_path)
{
	remove(f_path.c_str());
}

vector<string> File_sys::read_file(string f_path)
{
	vector<string> content;
	string aux;

	fstream file;
	file.open(f_path, ios::in);

	while (!file.eof())
	{
		getline(file, aux);
		content.push_back(aux);
	}

	return content;
}

void File_sys::write_file(string f_path, string content)
{
	fstream file;
	file.open(f_path, ios::out);

	file << content;
}

bool File_sys::file_exist(string f_path)
{
	fstream file;
	file.open(f_path);

	if (!file.fail())
		return true;

	else
		return false;
}

_off_t File_sys::get_size(string f_path)
{
	struct stat sb{};

	if (!stat(f_path.c_str(), &sb))
		return sb.st_size;

	else
		return _off_t(0);
}

string File_sys::get_type(string f_path)
{
	fstream file;
	file.open(f_path);

	if (file.fail() && Dir_sys::dir_exist(f_path))
		return "folder";

	else if (File_sys::file_exist(f_path))
		return "file";

	else
		return "null";
}