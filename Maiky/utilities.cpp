#include <string>
#include <vector>

#include "utilities.hpp"

using namespace std;

vector<string> Utils::split_string(string source)
{
	vector<string> split;

	string buff = "";

	for (int i = 0; i < source.size(); i++)
	{
		while (source[i] != ' ' && i < source.size())
			buff += source[i++];
		
		split.push_back(buff);
		buff = "";
	}

	return split;
}

string Utils::concat_string(vector<string> source)
{
	string full = "";

	for (int i = 0; i < source.size(); i++)
		full += source[i] + ((i + 1 < source.size()) ? " " : "");
	
	return full;
}