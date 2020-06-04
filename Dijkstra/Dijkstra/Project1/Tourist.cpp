#include <iostream>
#include <vector>
#include "Tourist.h"
#include "Graph.h"
using namespace  std;
void menu()
{
	cout << "**********菜单**********\n"
		<< "1.查询景点\n"
		<< "2.旅游导航\n"
		<< "3.搜索最短路径\n"
		<< "4.铺设电路\n"
		<< "0.退出" << endl;
}

void queryVex()
{
	cout << "**********查询景点**********" << endl;
	showVex();
	int choice = -1;
	cout << "请输入要查询的景点编号:";
	cin >> choice;
	vex v;
	if (-1 == getVex(choice,&v))
	{
		cout << "景点编号错误" << endl;
		return;
	}
	cout << v.name << endl
		<< v.description << endl;
	vector<edge> e;
	if (-1 == getEdge(choice, &e))
	{
		cout << "景点编号错误" << endl;
		return;
	}
	cout << "**********周边景区**********" << endl;
	for (auto temp : e)
	{
		vex u;
		getVex(temp.to, &u);
		cout << v.name << "->" << u.name << " " << temp.distance << endl;
	}
}

void guideTourist()
{
	cout << "**********旅游导航**********" << endl;
	showVex();
	int choice = -1;
	cout << "请输入您现在所在景区编号:";
	cin >> choice;
	guide(choice);
}

void findMinWay()
{
	cout << "**********搜索最短路径**********" << endl;
	showVex();
	int startVex = -1;
	int endVex = -1;
	cout << "请输入起始景区: ";
	cin >> startVex;
	cout << "请输入目标景区: ";
	cin >> endVex;
	int ans = dijkstra(startVex, endVex);
	if (ans == -1)
	{
		cout << "景区编号错误" << endl;
		return;
	}
	else if (ans == 0)
	{
		cout << "无法到达" << endl;
		return;
	}
	else
	{
		cout << "最短距离为: " << ans << endl;
		return;
	}
}

void electricity()
{
	cout << "**********铺设电路**********" << endl;
	Kruskal();
}