#include <iostream>
#include <string>

#include "buffer.hpp"

using namespace std;

void Buffer::operator<<(string value)
{
	cout << value;
}