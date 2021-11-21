#include<iostream>
#include<string>
#include<unordered_map>
#define NUMBER 128
using namespace std;

template <typename E>
class HuffNode {
public:
	~HuffNode() {};		//基本析构函数
	virtual int weight() = 0;	//返回频度
	virtual bool isLeaf() = 0;	//返回是否是叶子节点
};

template <typename E>
class LeafNode : public HuffNode<E> {
private:
	E it;	//值
	int wgt;//权重
public:
	LeafNode(const E& val, int freq) { it = val; wgt = freq; }//构造函数
	int weight() { return wgt; }
	E val() { return it; }
	bool isLeaf() { return true; }
};

template <typename E>
class IntlNode : public HuffNode<E> {
private:
	HuffNode<E>* lc;	//左孩子
	HuffNode<E>* rc;	//右孩子
	int wgt;			//左右孩子的权重之和
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r) { lc = l; rc = r; wgt = l->weight() + r->weight(); }//构造函数
	int weight() { return wgt; }							//返回权重
	bool isLeaf() { return false; }							//返回是否为叶子
	HuffNode<E>* left() const { return lc; }				//返回左孩子
	HuffNode<E>* right() const { return rc; }				//返回右孩子
	void setLeft(HuffNode<E>* b) { lc = (HuffNode<E>*)b; }	//设置左孩子
	void setRight(HuffNode<E>* b) { rc = (HuffNode<E>*)b; } //设置右孩子
};

template <typename E>
class HuffTree {

private:
	HuffNode<E>* Root;   //根节点
public:
	HuffTree(E& val, int freq) { Root = new LeafNode<E>(val, freq); } //构造函数
	HuffTree(HuffTree<E>* l, HuffTree<E>* r)						  //构造函数
	{
		Root = new IntlNode<E>(l->root(), r->root());
	}
	~HuffTree() {}			//析构函数
	HuffNode<E>* root() { return Root; }	//返回根节点
	int weight() { return Root->weight(); } //返回权重

	// 前序遍历Huffman编码树，将叶子结点的权重输出
	void proTra(HuffNode<E>* root) {
		if (root == NULL)return;
		if (root->isLeaf()) {
			cout << root->weight() << endl;
			return;
		}
		cout << root->weight() << endl;
		proTra(((IntlNode<E>*)root)->left());
		proTra(((IntlNode<E>*)root)->right());
	}
	// 前序遍历一颗Huffman编码树，将叶子结点的权重输出
	void proT() { proTra(Root); }

	// 从所有树中选出权重最小的两颗(m1为最小的,m2为第二小的)
	template <typename E>
	static void chose_min2(HuffTree<E>** t, int& m1, int& m2, int n) {
		m1 = 0;
		m2 = 0;
		int temp = t[0]->weight();
		for (int i = 0; i < n; i++) {
			if (t[i]->weight() < temp) {
				temp = t[i]->weight();
				m1 = i;
			}
		}
		if (m1 == 0) {
			temp = t[1]->weight();
		}
		else {
			temp = t[0]->weight();
		}
		for (int i = 0; i < n; i++) {
			if (i != m1 && t[i]->weight() <= temp) {
				m2 = i;
				temp = t[i]->weight();
			}
		}
	}

	//建树
	template <typename E>
	static HuffTree<E>* HuffmanBuild(char* s, int* w, int n) {
		HuffTree<E>* ttree[NUMBER];
		HuffTree<E>* temp;

		for (int i = 0; i < n; i++) {
			ttree[i] = new HuffTree<E>(s[i], w[i]);
		}

		while (n > 1) {
			n--;
			int m1, m2;
			chose_min2<char>(ttree, m1, m2, n + 1);
			temp = new HuffTree<E>(ttree[m1], ttree[m2]);
			ttree[m1] = temp;
			for (int i = m2; i < n; i++) {
				ttree[i] = ttree[i + 1];
			}
		}
		return ttree[0];
	}

	// 在控制台打印编码后的结果
	template <typename E>
	static void printHuffmanCode(HuffNode<E>* root, string s) {
		if (root == NULL) return;
		string printStr = "";
		if (((LeafNode<E>*)root)->val() == ' ') {
			printStr = "<space>";
		}
		else if (((LeafNode<E>*)root)->val() == '\n') {
			printStr = "\\n";
		}
		else if (((LeafNode<E>*)root)->val() == '\t') {
			printStr = "\\t";
		}
		else {
			printStr.push_back(((LeafNode<E>*)root)->val());
		}
		if (root->isLeaf()) {
			cout << printStr << "\t" << root->weight() << "\t" << s << endl;
			return;
		}
		HuffTree<E>::printHuffmanCode(((IntlNode<E>*)root)->left(), s + "0");
		HuffTree<E>::printHuffmanCode(((IntlNode<E>*)root)->right(), s + "1");
	}

	// 得到编码结果，用于在基本要求中写入到文件
	// return: 编码结果，是一个长字符串
	static string huffmanCode(HuffNode<char>* root, string s) {
		if (root == NULL) return "";
		string ret = "";
		string printStr = "";
		if (((LeafNode<char>*)root)->val() == ' ') {
			printStr = "<space>";
		}
		else if (((LeafNode<E>*)root)->val() == '\n') {
			printStr = "\\n";
		}
		else if (((LeafNode<E>*)root)->val() == '\t') {
			printStr = "\\t";
		}
		else {
			printStr.push_back(((LeafNode<E>*)root)->val());
		}

		if (root->isLeaf()) {
			ret += printStr + " " + s + "\n";
		}
		else {
			ret += HuffTree<E>::huffmanCode(((IntlNode<E>*)root)->left(), s + "0");
			ret += HuffTree<E>::huffmanCode(((IntlNode<E>*)root)->right(), s + "1");
		}
		return ret;
	}

	/*
	* 用map存储huffman编码的结果
	* 
	*/
	static void storeHuffmanCode(HuffNode<char>* root, 
		unordered_map<char, std::string>& code_map, string s = "")
	{
		if (root == NULL) return;
		if (root->isLeaf()) {
			/*code_map.insert(std::make_pair<char, std::string>
				(((LeafNode<char>*)root)->val(), s));*/
			code_map.insert({((LeafNode<char>*)root)->val(), s});
			return;
		}
		HuffTree<E>::storeHuffmanCode(((IntlNode<E>*)root)->left(), code_map, s + "0");
		HuffTree<E>::storeHuffmanCode(((IntlNode<E>*)root)->right(), code_map, s + "1");
	}
};

