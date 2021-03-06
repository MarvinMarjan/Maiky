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

int Utils::find_val_array(string val, vector<string> target)
{
	for (int i = 0; i < target.size(); i++)
		if (target[i] == val)
			return i;

	return -1;
}

vector<string> Utils::erase(vector<string> target, int start, int end)
{
	vector<string> new_array;

	for (int i = 0; i < target.size(); i++)
		if (i <= start || i > end)
			new_array.push_back(target[i]);
	
	return new_array;
}