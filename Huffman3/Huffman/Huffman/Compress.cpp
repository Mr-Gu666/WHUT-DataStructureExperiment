#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include "Huffman.h"
#include "Compress.h"

using namespace std;
int weight[256];
HNode huffman_tree[511];
HCode huffman_code[256];
vector<string> vstr;
vector<unsigned char> byte;
vector<string> restr;
//string byte转换过程中 出现的数字（由二进制转换而来）
vector<int> between;
int addLen;

void compress(string file_name)
{
	ifstream file_in;
	file_in.open(file_name, ios::in | ios::binary);
	if (!file_in.is_open())
	{
		cout << "Compress.cpp void compress() 文件未打开" << endl;
		return;
	}
	memset(weight, 0, sizeof weight);
	int ch = -1;
	while ((ch = file_in.get()) != EOF)
	{
		++weight[ch];
	}
	file_in.close();
	file_in.open(file_name, ios::in | ios::binary);
	file_in.seekg(0, ios::end);
	size_t size = file_in.tellg();
	file_in.close();

	//test_weight();
	makeHuffmanTree();
	//testHuffmanTree();
	encodeHuffman();
	//testHuffmanCode();
	string mergecode = mergeHCode();
	//cout << mergecode << endl;
	splitstr(mergecode);
	//testVstr();
	turnStringToByte();
	//testByte();
	//turnBytetoString();
	//testRestr();

	string newFileName = file_name + ".huf";
	fstream outFile;
	outFile.open(newFileName,ios::out|ios::binary);
	if (!outFile.is_open())
	{
		cout << "打开.huf文件失败" << endl;
		return;
	}
	int n = byte.size();
	for (int i = 0; i < 256; ++i)
	{
		outFile << weight[i];
	}
	outFile << addLen;
	for (int i = 0; i < n; ++i)
	{
		outFile << byte[i];
	}
	outFile.close();
	outFile.open(newFileName, ios::in | ios::binary);
	outFile.seekg(0, ios::end);
	size_t afterNum = outFile.tellg();
	outFile.close();

	cout << "原大小：" << size << "\n";
	cout << "现大小：" << afterNum << "\n";
	printf("压缩比例为：%.5lf\n", 1.0 * afterNum / size);
}

void test_weight()
{
	for (int i = 0; i < 256; ++i)
	{
		cout << weight[i] << endl;
	}
}

//开始在数组中构造Huffman树的结构
int Select(int n)
{
	int minValue = 0x7FFFFFFF;
	int minIndex = -1;
	for (int i = 0; i < n; ++i)
	{
		if (huffman_tree[i].weight < minValue && huffman_tree[i].parent == -1)
		{
			minValue = huffman_tree[i].weight;
			minIndex = i;
		}
	}
	return minIndex;
}

void makeHuffmanTree()
{
	for (int i = 0; i < 256; ++i)
	{
		huffman_tree[i] = HNode(weight[i]);
	}
	for (int i = 256; i < 511; ++i)
	{
		int s1 = Select(i);
		huffman_tree[s1].parent = i;
		int s2 = Select(i);
		huffman_tree[s2].parent = i;
		huffman_tree[i] = HNode(huffman_tree[s1].weight + huffman_tree[s2].weight, -1, s1, s2);
	}
}

void testHuffmanTree()
{
	for (int i = 0; i < 511; ++i)
	{
		cout << huffman_tree[i].weight << " " << huffman_tree[i].parent << " " << huffman_tree[i].lchild << " " << huffman_tree[i].rchild << endl;
	}
}

//根据Huffman树的结构得到Huffman编码
void bfs(int n, string s)
{
	if (huffman_tree[n].lchild == -1 && huffman_tree[n].rchild == -1)
	{
		huffman_code[n] = HCode(huffman_tree[n].weight, s);
		return;
	}
	if (huffman_tree[n].lchild != -1)
	{
		bfs(huffman_tree[n].lchild, s + "0");
	}
	if (huffman_tree[n].rchild != -1)
	{
		bfs(huffman_tree[n].rchild, s + "1");
	}
}

void encodeHuffman()
{
	int start = 510;
	bfs(start, "");
}

void testHuffmanCode()
{
	for (int i = 0; i < 256; ++i)
	{
		cout << huffman_code[i].weight << " " << huffman_code[i].code << endl;
	}
}

//合并所以Huffman编码
string mergeHCode()
{
	string str = "";
	for (int i = 0; i < 256; ++i)
	{
		str += huffman_code[i].code;
	}
	return str;
}

//将Huffman编码分为8位一组，末尾添0
void splitstr(string s)
{
	int n = s.length();
	addLen = n % 8 == 0 ? 0 : (8 - n % 8);
	for (int i = 0; i < addLen; ++i)
	{
		s += "0";
	}
	int m = s.length() / 8;
	for (int i = 0; i < m; ++i)
	{
		vstr.push_back(s.substr(i * 8, 8));
		//cout << s.substr(i * 8, (i + 1) * 8) << endl;
	}
}

void testVstr()
{
	int n = vstr.size();
	for (int i = 0; i < n; ++i)
	{
		cout << vstr[i] << endl;
	}
}

//将8位的字符串转换为byte
void turnStringToByte()
{
	int n = vstr.size();
	for (int i = 0; i < n; ++i)
	{
		string str = vstr[i];
		unsigned char temp = 0;
		for (int i = 0; i < 8; ++i)
		{
			temp = temp << 1;
			if (str[i] == '1')
			{
				++temp;
			}
		}
		byte.push_back(temp);
		between.push_back(temp);
	}
}

void testByte()
{
	int n = byte.size();
	for (int i = 0; i < n; ++i)
	{
		cout << byte[i] << endl;
	}
}

//将byte还原成string
void turnBytetoString()
{
	int n = byte.size();
	for (int i = 0; i < n; ++i)
	{
		unsigned char temp = byte[i];
		string str = "";
		while (temp)
		{
			if (temp % 2 == 1)
			{
				str = "1" + str;
			}
			else
			{
				str = "0" + str;
			}
			temp = temp >> 1;
		}
		while (str.size() < 8)
		{
			str = "0" + str;
		}
		restr.push_back(str);
	}
}

void testRestr()
{
	int n = vstr.size();
	for (int i = 0; i < n; ++i)
	{
		//cout << vstr[i] << " " << restr[i] << endl;
		cout << vstr[i] << " " << between[i] << " " << restr[i] << endl;
	}
}