#include <iostream>
#include <cstdio>
#include "Graph.h"
#include "Tourist.h"
using namespace std;
int main()
{
	if (-1 == init())
	{
		return -1;
	}
	int choice = 1;
	while (0 != choice)
	{
		menu();
		cout << "��ѡ�����";
		cin >> choice;
		switch (choice)
		{
		case 1:
			queryVex();
			break;
		case 0:
			break;
		case 2:
			guideTourist();
			break;
		case 3:
			findMinWay();
			break;
		case 4:
			electricity();
			break;
		default:
			cout << "����������ѡ��" << endl;
			break;
		}
		getchar();
		getchar();
	}
	return 0;
}