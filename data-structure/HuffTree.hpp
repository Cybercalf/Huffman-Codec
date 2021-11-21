#include<iostream>
#include<string>
#include<unordered_map>
#define NUMBER 128
using namespace std;

template <typename E>
class HuffNode {
public:
	~HuffNode() {};		//������������
	virtual int weight() = 0;	//����Ƶ��
	virtual bool isLeaf() = 0;	//�����Ƿ���Ҷ�ӽڵ�
};

template <typename E>
class LeafNode : public HuffNode<E> {
private:
	E it;	//ֵ
	int wgt;//Ȩ��
public:
	LeafNode(const E& val, int freq) { it = val; wgt = freq; }//���캯��
	int weight() { return wgt; }
	E val() { return it; }
	bool isLeaf() { return true; }
};

template <typename E>
class IntlNode : public HuffNode<E> {
private:
	HuffNode<E>* lc;	//����
	HuffNode<E>* rc;	//�Һ���
	int wgt;			//���Һ��ӵ�Ȩ��֮��
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r) { lc = l; rc = r; wgt = l->weight() + r->weight(); }//���캯��
	int weight() { return wgt; }							//����Ȩ��
	bool isLeaf() { return false; }							//�����Ƿ�ΪҶ��
	HuffNode<E>* left() const { return lc; }				//��������
	HuffNode<E>* right() const { return rc; }				//�����Һ���
	void setLeft(HuffNode<E>* b) { lc = (HuffNode<E>*)b; }	//��������
	void setRight(HuffNode<E>* b) { rc = (HuffNode<E>*)b; } //�����Һ���
};

template <typename E>
class HuffTree {

private:
	HuffNode<E>* Root;   //���ڵ�
public:
	HuffTree(E& val, int freq) { Root = new LeafNode<E>(val, freq); } //���캯��
	HuffTree(HuffTree<E>* l, HuffTree<E>* r)						  //���캯��
	{
		Root = new IntlNode<E>(l->root(), r->root());
	}
	~HuffTree() {}			//��������
	HuffNode<E>* root() { return Root; }	//���ظ��ڵ�
	int weight() { return Root->weight(); } //����Ȩ��

	// ǰ�����Huffman����������Ҷ�ӽ���Ȩ�����
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
	// ǰ�����һ��Huffman����������Ҷ�ӽ���Ȩ�����
	void proT() { proTra(Root); }

	// ����������ѡ��Ȩ����С������(m1Ϊ��С��,m2Ϊ�ڶ�С��)
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

	//����
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

	// �ڿ���̨��ӡ�����Ľ��
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

	// �õ��������������ڻ���Ҫ����д�뵽�ļ�
	// return: ����������һ�����ַ���
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
	* ��map�洢huffman����Ľ��
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

