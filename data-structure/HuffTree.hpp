#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#define NUMBER 128
using namespace std;

template <typename E>
class HuffNode
{
public:
	~HuffNode() {};			   //基本析构函数
	virtual int weight() = 0;  //返回频度
	virtual bool isLeaf() = 0; //返回是否是叶子节点
};

template <typename E>
class LeafNode : public HuffNode<E>
{
private:
	E it;	 //值
	int wgt; //权重
public:
	LeafNode(const E& val, int freq)
	{
		it = val;
		wgt = freq;
	} //构造函数
	int weight() { return wgt; }
	E val() { return it; }
	bool isLeaf() { return true; }
};

template <typename E>
class IntlNode : public HuffNode<E>
{
private:
	HuffNode<E>* lc; //左孩子
	HuffNode<E>* rc; //右孩子
	int wgt;		 //左右孩子的权重之和
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r)
	{
		lc = l;
		rc = r;
		wgt = l->weight() + r->weight();
	}														 //构造函数
	int weight() { return wgt; }							 //返回权重
	bool isLeaf() { return false; }							 //返回是否为叶子
	HuffNode<E>* left() const { return lc; }				 //返回左孩子
	HuffNode<E>* right() const { return rc; }				 //返回右孩子
	void setLeft(HuffNode<E>* b) { lc = (HuffNode<E> *)b; }	 //设置左孩子
	void setRight(HuffNode<E>* b) { rc = (HuffNode<E> *)b; } //设置右孩子
};

template <typename E>
class HuffTree
{

private:
	HuffNode<E>* Root; //根节点
public:
	HuffTree(E& val, int freq) { Root = new LeafNode<E>(val, freq); } //构造函数
	HuffTree(HuffTree<E>* l, HuffTree<E>* r)						  //构造函数
	{
		Root = new IntlNode<E>(l->root(), r->root());
	}
	/*析构函数*/
	~HuffTree()
	{
		clear(Root);
	}
	/*用于析构函数*/
	void clear(HuffNode<E>* root)
	{
		if (root == NULL)
			return;
		if (!root->isLeaf())
		{
			clear(((IntlNode<E> *)root)->left());
			clear(((IntlNode<E> *)root)->right());
		}
		delete root;
	}

	HuffNode<E>* root() { return Root; }	//返回根节点
	int weight() { return Root->weight(); } //返回权重

	/*
	* 从所有树中选出权重最小的两颗
	* t为HuffTree数组,即在建树过程中的形成的森林
	* m1,m2用于存放权重最小的两棵树m1为最小的那颗
	* n为HuffTree数组的大小
	*/
	static void chose_min2(HuffTree<E>** t, int& m1, int& m2, int n)
	{
		m1 = 0;
		m2 = 0;
		//遍历数组找出最小的那棵树
		int temp = t[0]->weight();
		for (int i = 0; i < n; i++)
		{
			if (t[i]->weight() < temp)
			{
				temp = t[i]->weight();
				m1 = i;
			}
		}
		//第二遍遍历找出最小的第二颗
		if (m1 == 0)
		{
			temp = t[1]->weight();
		}
		else
		{
			temp = t[0]->weight();
		}
		for (int i = 0; i < n; i++)
		{
			if (i != m1 && t[i]->weight() <= temp)
			{
				m2 = i;
				temp = t[i]->weight();
			}
		}
	}

	/*
	* 根据字符集、频度集、字符总数来构建Huffman编码树
	* s: 字符集，记录出现过的字符
	* w: 频度集，记录字符出现的频度
	* n: 记录出现过的字符数量
	*/
	static HuffTree<char>* HuffmanBuild(char* s, int* w, int n)
	{
		HuffTree<char>* ttree[NUMBER];
		HuffTree<char>* temp;

		//遍历s,w构造n棵HuffTree
		for (int i = 0; i < n; i++)
		{
			ttree[i] = new HuffTree<char>(s[i], w[i]);
		}

		//重复合并权重最小的两棵树,直至只剩下一棵树
		while (n > 1)
		{
			n--;
			int m1, m2;
			chose_min2(ttree, m1, m2, n + 1);
			temp = new HuffTree<char>(ttree[m1], ttree[m2]);
			ttree[m1] = temp;
			for (int i = m2; i < n; i++)
			{
				ttree[i] = ttree[i + 1];
			}
		}
		//返回剩下的那棵树,即建好的树
		return ttree[0];
	}

	/*
	* 遍历Huffman编码树，在控制台打印统计与编码映射表
	* root: 树的根节点
	* s: 二进制编码信息字符串，由0和1字符构成，用于递归
	*/
	static void printHuffmanCode(HuffNode<char>* root, string s = "")
	{
		// 为空直接return
		if (root == NULL)
			return;
		string printStr = "";
		// 下面是对一些特殊字符串进行处理, 避免打印时打乱格式
		if (((LeafNode<char> *)root)->val() == ' ')
		{
			printStr = "<space>";
		}
		else if (((LeafNode<char> *)root)->val() == '\n')
		{
			printStr = "\\n";
		}
		else if (((LeafNode<char> *)root)->val() == '\t')
		{
			printStr = "\\t";
		}
		else
		{
			printStr.push_back(((LeafNode<char> *)root)->val());
		}
		// 遇到叶子节点就打印其中储存的字符，权重，编码结果
		if (root->isLeaf())
		{
			cout << printStr << "\t" << root->weight() << "\t" << s << endl;
			return;
		}
		//递归访问左右孩子
		HuffTree<char>::printHuffmanCode(((IntlNode<char> *)root)->left(), s + "0");
		HuffTree<char>::printHuffmanCode(((IntlNode<char> *)root)->right(), s + "1");
	}

	// 得到编码结果，用于在基本要求中写入到文件
	// root: 树的根节点
	// s: 二进制编码信息字符串，由0和1字符构成，用于递归
	// return: 编码结果，是一个长字符串
	static string huffmanCode(HuffNode<char>* root, string s = "")
	{
		if (root == NULL)
			return "";
		string ret = "";
		string printStr = "";
		// 下面是对一些特殊字符串进行处理, 避免打印时打乱格式
		if (((LeafNode<char> *)root)->val() == ' ')
		{
			printStr = "<space>";
		}
		else if (((LeafNode<char> *)root)->val() == '\n')
		{
			printStr = "\\n";
		}
		else if (((LeafNode<char> *)root)->val() == '\t')
		{
			printStr = "\\t";
		}
		else
		{
			printStr.push_back(((LeafNode<char> *)root)->val());
		}

		if (root->isLeaf())
		{
			ret += printStr + " " + s + "\n";
		}
		else
		{
			ret += HuffTree<char>::huffmanCode(((IntlNode<char> *)root)->left(), s + "0");
			ret += HuffTree<char>::huffmanCode(((IntlNode<char> *)root)->right(), s + "1");
		}
		return ret;
	}

	/*
	* 用map存储huffman编码的结果
	* root: 树的根节点
	* code_map: 从字符到01字符串的映射表
	* s: 二进制编码信息字符串，由0和1字符构成，用于递归
	*/
	static void storeHuffmanCode(HuffNode<char>* root,
		unordered_map<char, std::string>& code_map, string s = "")
	{
		if (root == NULL)
			return;
		if (root->isLeaf())
		{
			/*code_map.insert(std::make_pair<char, std::string>
				(((LeafNode<char>*)root)->val(), s));*/
			code_map.insert({ ((LeafNode<char> *)root)->val(), s });
			return;
		}
		HuffTree<char>::storeHuffmanCode(((IntlNode<char> *)root)->left(), code_map, s + "0");
		HuffTree<char>::storeHuffmanCode(((IntlNode<char> *)root)->right(), code_map, s + "1");
	}
};
