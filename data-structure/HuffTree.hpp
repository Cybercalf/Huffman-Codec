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
	~HuffNode() {};			   //������������
	virtual int weight() = 0;  //����Ƶ��
	virtual bool isLeaf() = 0; //�����Ƿ���Ҷ�ӽڵ�
};

template <typename E>
class LeafNode : public HuffNode<E>
{
private:
	E it;	 //ֵ
	int wgt; //Ȩ��
public:
	LeafNode(const E& val, int freq)
	{
		it = val;
		wgt = freq;
	} //���캯��
	int weight() { return wgt; }
	E val() { return it; }
	bool isLeaf() { return true; }
};

template <typename E>
class IntlNode : public HuffNode<E>
{
private:
	HuffNode<E>* lc; //����
	HuffNode<E>* rc; //�Һ���
	int wgt;		 //���Һ��ӵ�Ȩ��֮��
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r)
	{
		lc = l;
		rc = r;
		wgt = l->weight() + r->weight();
	}														 //���캯��
	int weight() { return wgt; }							 //����Ȩ��
	bool isLeaf() { return false; }							 //�����Ƿ�ΪҶ��
	HuffNode<E>* left() const { return lc; }				 //��������
	HuffNode<E>* right() const { return rc; }				 //�����Һ���
	void setLeft(HuffNode<E>* b) { lc = (HuffNode<E> *)b; }	 //��������
	void setRight(HuffNode<E>* b) { rc = (HuffNode<E> *)b; } //�����Һ���
};

template <typename E>
class HuffTree
{

private:
	HuffNode<E>* Root; //���ڵ�
public:
	HuffTree(E& val, int freq) { Root = new LeafNode<E>(val, freq); } //���캯��
	HuffTree(HuffTree<E>* l, HuffTree<E>* r)						  //���캯��
	{
		Root = new IntlNode<E>(l->root(), r->root());
	}
	/*��������*/
	~HuffTree()
	{
		clear(Root);
	}
	/*������������*/
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

	HuffNode<E>* root() { return Root; }	//���ظ��ڵ�
	int weight() { return Root->weight(); } //����Ȩ��

	/*
	* ����������ѡ��Ȩ����С������
	* tΪHuffTree����,���ڽ��������е��γɵ�ɭ��
	* m1,m2���ڴ��Ȩ����С��������m1Ϊ��С���ǿ�
	* nΪHuffTree����Ĵ�С
	*/
	static void chose_min2(HuffTree<E>** t, int& m1, int& m2, int n)
	{
		m1 = 0;
		m2 = 0;
		//���������ҳ���С���ǿ���
		int temp = t[0]->weight();
		for (int i = 0; i < n; i++)
		{
			if (t[i]->weight() < temp)
			{
				temp = t[i]->weight();
				m1 = i;
			}
		}
		//�ڶ�������ҳ���С�ĵڶ���
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
	* �����ַ�����Ƶ�ȼ����ַ�����������Huffman������
	* s: �ַ�������¼���ֹ����ַ�
	* w: Ƶ�ȼ�����¼�ַ����ֵ�Ƶ��
	* n: ��¼���ֹ����ַ�����
	*/
	static HuffTree<char>* HuffmanBuild(char* s, int* w, int n)
	{
		HuffTree<char>* ttree[NUMBER];
		HuffTree<char>* temp;

		//����s,w����n��HuffTree
		for (int i = 0; i < n; i++)
		{
			ttree[i] = new HuffTree<char>(s[i], w[i]);
		}

		//�ظ��ϲ�Ȩ����С��������,ֱ��ֻʣ��һ����
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
		//����ʣ�µ��ǿ���,�����õ���
		return ttree[0];
	}

	/*
	* ����Huffman���������ڿ���̨��ӡͳ�������ӳ���
	* root: ���ĸ��ڵ�
	* s: �����Ʊ�����Ϣ�ַ�������0��1�ַ����ɣ����ڵݹ�
	*/
	static void printHuffmanCode(HuffNode<char>* root, string s = "")
	{
		// Ϊ��ֱ��return
		if (root == NULL)
			return;
		string printStr = "";
		// �����Ƕ�һЩ�����ַ������д���, �����ӡʱ���Ҹ�ʽ
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
		// ����Ҷ�ӽڵ�ʹ�ӡ���д�����ַ���Ȩ�أ�������
		if (root->isLeaf())
		{
			cout << printStr << "\t" << root->weight() << "\t" << s << endl;
			return;
		}
		//�ݹ�������Һ���
		HuffTree<char>::printHuffmanCode(((IntlNode<char> *)root)->left(), s + "0");
		HuffTree<char>::printHuffmanCode(((IntlNode<char> *)root)->right(), s + "1");
	}

	// �õ��������������ڻ���Ҫ����д�뵽�ļ�
	// root: ���ĸ��ڵ�
	// s: �����Ʊ�����Ϣ�ַ�������0��1�ַ����ɣ����ڵݹ�
	// return: ����������һ�����ַ���
	static string huffmanCode(HuffNode<char>* root, string s = "")
	{
		if (root == NULL)
			return "";
		string ret = "";
		string printStr = "";
		// �����Ƕ�һЩ�����ַ������д���, �����ӡʱ���Ҹ�ʽ
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
	* ��map�洢huffman����Ľ��
	* root: ���ĸ��ڵ�
	* code_map: ���ַ���01�ַ�����ӳ���
	* s: �����Ʊ�����Ϣ�ַ�������0��1�ַ����ɣ����ڵݹ�
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
