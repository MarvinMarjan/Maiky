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
		if (source[i] == '\"')
		{
			i++;

			while (source[i] != '\"')
			{
				buff += (source[i] == '\\' && source[i + 1] == 'n') ? '\n' : source[i];

				if (source[i] == '\\')
					i++;

				i++;
			}

			split.push_back(buff);
			buff = "";

			continue;
		}

		if (source[i + 1] == 0 || source[i] == ' ')
		{
			if (source[i + 1] == 0)
				buff += source[i];

			split.push_back(buff);
			buff = "";
			continue;
		}

		buff += source[i];
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