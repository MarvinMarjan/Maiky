#include <document.h> // rapidjson/include/rapidjson/document.h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "bootstrap.hpp"
#include "code.hpp"

using namespace rapidjson;
using namespace std;

map<string, string> Bootstrap::check_runtime_config()
{
	map<string, string> configs;
	Document src;
	fstream rt_file;

	string buff;
	string full_doc = "";

	rt_file.open("__maiky_runtime_config__.json");

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

vector<string> Bootstrap::check_program_args(int argc, char* argv[])
{
	vector<string> vector_argv;

	for (int i = 1; i < argc; i++)
		vector_argv.push_back(argv[i]);

	string aux = "";

	// argv[0] == path_to_exec
	for (int i = 2; i < vector_argv.size(); i++)
	{
		if (vector_argv[i][0] == '\"')
		{
			aux += vector_argv[i];

			if (vector_argv[i][vector_argv[i].size() - 1] == '\"')
			{
				aux.erase(0, 1);
				aux.erase(aux.end() - 1);

				vector_argv.push_back(aux);

				break;
			}
		}
	}

	return vector_argv;
}

vector<string> Bootstrap::check_program_args(vector<string> args)
{
	vector<string> vector_argv;

	string aux = "";

	// argv[0] == path_to_exec
	for (int i = 0; i < args.size(); i++)
	{
		if (args[i][0] == '\"')
		{
			for (int o = i; o < args.size(); o++)
			{
				aux += args[o] + ' ';

				if (args[o][args[o].size() - 1] == '\"')
				{
					aux.erase(0, 1);
					aux.erase(aux.end() - 2);

					vector_argv.push_back(aux);

					i = o;
					break;
				}
			}
		}
	}

	return vector_argv;
}