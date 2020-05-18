#include <iostream>
#include <string>
#include "Compress.h"
using namespace std;
int main()
{
	string file_name;
	cout << "cin file name:";
	cin >> file_name;
	compress(file_name);
	return 0;
}