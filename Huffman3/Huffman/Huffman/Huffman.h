#pragma once
#ifndef HUFFMAN_H
#include <string>
struct HNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
	HNode() 
	{
		this->weight = 0;
		this->parent = -1;
		this->lchild = -1;
		this->rchild = -1;
	};
	HNode(int w)
	{
		this->weight = w;
		this->parent = -1;
		this->lchild = -1;
		this->rchild = -1;
	}
	HNode(int w,int p,int l,int r)
	{
		this->weight = w;
		this->parent = p;
		this->lchild = l;
		this->rchild = r;
	}
};

struct HCode
{
	int weight;
	std::string code;
	HCode()
	{
		this->weight = 0;
		this->code = "";
	}
	HCode(int w,std::string s)
	{
		this->weight = w;
		this->code = s;
	}
};

#define HUFFMAN_H
#endif // !HUFFMAN_H
