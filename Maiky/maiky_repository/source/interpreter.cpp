#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "interpreter.hpp"

using namespace std;

Interpreter::Interpreter()
{
	//this->file
}

void Interpreter::open(string path)
{
	this->file.open(path, ios::in);
}

vector<string> Interpreter::read()
{
	vector<string> _Buffer;

	while (!this->file.eof())
	{
		string aux;
		getline(this->file, aux);

		_Buffer.push_back(aux);
	}
	
	return _Buffer;
}