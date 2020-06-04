#include <iostream>
#include <vector>
#include "Tourist.h"
#include "Graph.h"
using namespace  std;
void menu()
{
	cout << "**********�˵�**********\n"
		<< "1.��ѯ����\n"
		<< "2.���ε���\n"
		<< "3.�������·��\n"
		<< "4.�����·\n"
		<< "0.�˳�" << endl;
}

void queryVex()
{
	cout << "**********��ѯ����**********" << endl;
	showVex();
	int choice = -1;
	cout << "������Ҫ��ѯ�ľ�����:";
	cin >> choice;
	vex v;
	if (-1 == getVex(choice,&v))
	{
		cout << "�����Ŵ���" << endl;
		return;
	}
	cout << v.name << endl
		<< v.description << endl;
	vector<edge> e;
	if (-1 == getEdge(choice, &e))
	{
		cout << "�����Ŵ���" << endl;
		return;
	}
	cout << "**********�ܱ߾���**********" << endl;
	for (auto temp : e)
	{
		vex u;
		getVex(temp.to, &u);
		cout << v.name << "->" << u.name << " " << temp.distance << endl;
	}
}

void guideTourist()
{
	cout << "**********���ε���**********" << endl;
	showVex();
	int choice = -1;
	cout << "���������������ھ������:";
	cin >> choice;
	guide(choice);
}

void findMinWay()
{
	cout << "**********�������·��**********" << endl;
	showVex();
	int startVex = -1;
	int endVex = -1;
	cout << "��������ʼ����: ";
	cin >> startVex;
	cout << "������Ŀ�꾰��: ";
	cin >> endVex;
	int ans = dijkstra(startVex, endVex);
	if (ans == -1)
	{
		cout << "������Ŵ���" << endl;
		return;
	}
	else if (ans == 0)
	{
		cout << "�޷�����" << endl;
		return;
	}
	else
	{
		cout << "��̾���Ϊ: " << ans << endl;
		return;
	}
}

void electricity()
{
	cout << "**********�����·**********" << endl;
	Kruskal();
}