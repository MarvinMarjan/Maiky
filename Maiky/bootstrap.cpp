#include <document.h> // rapidjson/include/rapidjson/document.h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "bootstrap.hpp"

using namespace rapidjson;
using namespace std;

map<string, string> Bootstrap::check_runtime_config()
{
	map<string, string> configs;
	Document src;
	fstream rt_file;

	string buff;
	string full_doc = "";

	rt_file.open("./__maiky_runtime_config__.json");

	while (!rt_file.eof())
	{
		getline(rt_file, buff);
		full_doc += buff;
	}

	src.Parse(full_doc.c_str());

	Value& path_key = src["path"];
	Value& args_key = src["args"];

	string path_val = path_key.GetString();
	string args_val = args_key.GetString();
	
	configs.insert(pair<string, string>({ "path", path_val }));
	configs.insert(pair<string, string>({ "args", args_val }));

	return configs;
}