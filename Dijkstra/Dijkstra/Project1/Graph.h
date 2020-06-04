#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>
#include <queue>
struct vex
{
	//节点编号
	int num;
	//节点名称
	std::string name;
	//节点描述
	std::string description;
	vex() {}
	vex(int num, std::string name, std::string description) :num(num), name(name), description(description) {}
};

struct edge
{
	int to;
	int distance;
	edge() {}
	edge(int to, int distance) :to(to), distance(distance) {}
	bool operator < (const edge& b) const
	{
		return distance > b.distance;
	}
};

struct kruskal
{
	int u;
	int v;
	int w;
	kruskal(){}
	kruskal(int u,int v,int w):u(u),v(v),w(w){}
};

int init();
int readVex();
void testVexIn();
int changeCharToInt(char* buf);
int readEdge();
void testEdge();
void showVex();
int getVex(int index,vex* v);
int getEdge(int index, std::vector<edge>* e);
void guide(int sr);
void dfs(int sr,std::deque<std::string> a,std::vector<bool> vis);
int dijkstra(int start, int end);
int getF(int x);
void Kruskal();
#endif // !GRAPH_H
