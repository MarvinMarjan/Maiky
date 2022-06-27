#include <string>
#include <vector>

#include "condition.hpp"

using namespace std;

bool Condition::check(vector<string> itr)
{
	bool result;

	if (itr[0] == "true")
		return true;

	else if (itr[0] == "false")
		return false;

	else if (itr[1] == "==")
		result = (itr[0] == itr[2]);

	else if (itr[1] == "!=")
		result = (itr[0] != itr[2]);

	else if (itr[1] == ">")
		result = (stof(itr[0]) > stof(itr[2]));
		
	else if (itr[1] == "<")
		result = (stof(itr[0]) < stof(itr[2]));

	else if (itr[1] == ">=")
		result = (stof(itr[0]) >= stof(itr[2]));

	else if (itr[1] == "<=")
		result = (stof(itr[0]) <= stof(itr[2]));

	return result;
}

bool Condition::check_all(vector<vector<string>> conds)
{
	vector<bool> res = { Condition::check(conds[0]) };

	for (int i = 1; i < conds.size(); i++)
	{
		vector<string> cond = conds[i];

		if (cond[0] == "and")
		{
			if (res[0] && Condition::check(conds[i + 1]))
				res[0] = true;

			else
				res[0] = false;
		}

		else if (cond[0] == "or")
		{
			if (res[0] || Condition::check(conds[i + 1]))
				res[0] = true;

			else
				res[0] = false;
		}
	}

	return res[0];
}



vector<vector<string>> Condition::get_condition(vector<string> line)
{
	vector<vector<string>> conds;
	vector<string> aux;

	for (int i = 0; i < line.size(); i++)
	{
		if (i + 1 >= line.size() || line[i + 1] == "and" || line[i + 1] == "or")
		{
			aux.push_back(line[i]);
			conds.push_back(aux);

			if (i + 1 < line.size())
				conds.push_back({ line[i + 1] });

			aux = vector<string>();
			i++;
			continue;
		}

		aux.push_back(line[i]);
	}

	return conds;
}