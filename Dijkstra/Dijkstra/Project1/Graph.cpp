#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <stack>
#include <cstring>
#include "Graph.h"
using namespace std;
int vexNum;
vex vexs[20];
vector<edge> edges[20];
vector<deque<string>> ans;
int fa[20];
int init()
{
	vexNum = 0;
	if (-1 == readVex())
	{
		cout << "节点文件打开失败" << endl;
		return -1;
	}
	//testVexIn();
	if (-1 == readEdge())
	{
		cout << "边信息文件打开失败" << endl;
		return -1;
	}
	//testEdge();
	return 1;
}

int readVex()
{
	ifstream file_in;
	char buf[200];
	file_in.open("Vex.txt", ios::in);
	if (!file_in.is_open())
	{
		return -1;
	}
	file_in.getline(buf, '\r\n');
	vexNum = changeCharToInt(buf);
	for (int i = 0; i < vexNum; ++i)
	{
		file_in.getline(buf, '\r\n');
		vexs[i].num = changeCharToInt(buf);
		file_in.getline(buf, '\r\n');
		vexs[i].name = buf;
		file_in.getline(buf, '\r\n');
		vexs[i].description = buf;
	}
	file_in.close();
}

int changeCharToInt(char* buf)
{
	string s = buf;
	int len = s.length();
	int ans = 0;
	for (int i = 0; i < len; ++i)
	{
		ans *= 10;
		ans += s[i] - '0';
	}
	return ans;
}

void testVexIn()
{
	for (int i = 0; i < vexNum; ++i)
	{
		cout << vexs[i].num << " " << vexs[i].name << " " << vexs[i].description << endl;
	}
}

int readEdge()
{
	ifstream fileIn;
	fileIn.open("Edge.txt", ios::in);
	if (!fileIn.is_open())
	{
		return -1;
	}
	while (!fileIn.eof())
	{
		int a, b, c;
		fileIn >> a >> b >> c;
		edges[a].push_back(edge(b, c));
		edges[b].push_back(edge(a, c));
	}
	fileIn.close();
}

void testEdge()
{
	for (int i = 0; i < vexNum; ++i)
	{
		int len = edges[i].size();
		for (int j = 0; j < len; ++j)
		{
			cout << i << " " << edges[i][j].to << " " << edges[i][j].distance << endl;
		}
	}
}

void showVex()
{
	for (int i = 0; i < vexNum; ++i)
	{
		cout << vexs[i].num << "-" << vexs[i].name << endl;
	}
}

int getVex(int index,vex* v)
{
	if (index < 0 || index >= vexNum)
	{
		return -1;
	}
	*v = vexs[index];
	return 1;
}

int getEdge(int index, vector<edge>* e)
{
	if (index < 0 || index >= vexNum)
	{
		return -1;
	}
	*e = edges[index];
	return 1;
}

void guide(int sr)
{
	ans.clear();
	if (sr < 0 || sr >= vexNum)
	{
		cout << "景区编号错误" << endl;
		return;
	}
	vector<bool> vis(20, 0);
	deque<string> que;
	que.push_back(vexs[sr].name);
	dfs(sr, que, vis);
	int len = ans.size();
	for (int i = 0; i < len; ++i)
	{
		cout << "路线" << i + 1 << ": ";
		deque<string> q = ans[i];
		while (!q.empty())
		{
			string s = q.front();
			q.pop_front();
			cout << s;
		}
		cout << endl;
	}
}

void dfs(int sr,deque<string> que,vector<bool> vis)
{
	if (vis[sr] == true)
	{
		return;
	}
	if (que.size() == 2 * vexNum - 1)
	{
		ans.push_back(que);
		return;
	}
	for (auto e : edges[sr])
	{
		que.push_back("->");
		que.push_back(vexs[e.to].name);
		vis[sr] = true;
		dfs(e.to, que, vis);
		que.pop_back();
		que.pop_back();
		vis[sr] = false;
	}
}

int dijkstra(int start, int end)
{
	if (start < 0 || start >= vexNum || end < 0 || end >= vexNum)
	{
		return -1;
	}
	bool vis[20];
	int dis[20];
	int pre[20];
	memset(pre, -1, sizeof pre);
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	dis[start] = 0;
	//vis[start] = 1;
	priority_queue<edge> que;
	que.push(edge(start,0));
	while (!que.empty())
	{
		int now = que.top().to;
		que.pop();
		if (vis[now] == true)
		{
			continue;
		}
		vis[now] = true;
		for (auto e : edges[now])
		{
			if (!vis[e.to] && dis[e.to] > dis[now] + e.distance)
			{
				pre[e.to] = now;
				dis[e.to] = dis[now] + e.distance;
				que.push(edge(e.to,dis[e.to]));
			}
		}
	}
	if (dis[end] == 0x3f3f3f3f)
	{
		return 0;
	}
	else
	{
		int re = end;
		cout << "最短路径为: ";
		stack<int> ans;
		while (end != -1)
		{
			ans.push(end);
			end = pre[end];
		}
		cout << vexs[start].name;
		ans.pop();
		while (!ans.empty())
		{
			cout << "->" << vexs[ans.top()].name;
			ans.pop();
		}
		cout << endl;
		return dis[re];
	}
}

int getF(int x)
{
	if (x == fa[x])
	{
		return x;
	}
	else
	{
		return fa[x] = getF(fa[x]);
	}
}

bool cmp(const kruskal& a, const kruskal& b)
{
	return a.w < b.w;
}

void Kruskal()
{
	vector<kruskal> temp;
	vector<kruskal> re;
	int ans = 0;
	for (int i = 0; i < vexNum; ++i)
	{
		for (edge e : edges[i])
		{
			temp.push_back(kruskal(i,e.to,e.distance));
		}
	}
	sort(temp.begin(), temp.end(), cmp);
	int cnt = vexNum;
	for (int i = 0; i < 20; ++i)
	{
		fa[i] = i;
	}
	int len = temp.size();
	for (int i = 0; i < len; ++i)
	{
		int t1 = getF(temp[i].u);
		int t2 = getF(temp[i].v);
		if (t1 != t2)
		{
			fa[t1] = t2;
			ans += temp[i].w;
			re.push_back(kruskal(t1, t2, temp[i].w));
			if (cnt == 1)
			{
				break;
			}
			cnt--;
		}
	}
	cout << "在以下两个景点间铺设电路:" << endl;
	len = re.size();
	for (int i = 0; i < len; ++i)
	{
		cout << vexs[re[i].u].name << " - " << vexs[re[i].v].name << "    " << re[i].w << endl;
	}
	cout << "铺设电路的总长度为: " << ans << endl;
}