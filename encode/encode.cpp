#include "encode.h"
#include "../file-process/file-process.h"
#include "../data-structure/HuffTree.hpp"
#include "../statistics/statistics.h"
using namespace std;





void encode_process() {
	/* ���ļ��л�ȡ��Ϣ����һ���ַ��� */
	static string file_path = ""; // �洢�ļ�·��
	static string file_content = ""; // �洢�ļ�����
	file_path = FileProcess::getFilePath("ѡ��ԭ�ļ�", TEXT_MODE); // ��ȡ�û���ѡ�ļ���·��
	if (file_path.compare("NONE") == 0) { // ����û�û��ѡ���ļ�
		MessageBox(NULL, TEXT("û��ѡ���ı��ļ����޷�����"),
			NULL, MB_ICONERROR); // ����������ʾ�Ի���
	}
	else { // ����û�����ѡ���ļ�
		printf("\nѡ���ļ���%s\n\n���ڱ���...\n", file_path.c_str());
		file_content = FileProcess::readTextContent(file_path.c_str()); // ��ȡ�ļ��е�ȫ�����ݣ������ַ���

		/* �����ַ�����ͳ��ÿһ���ַ��ĳ���Ƶ�� */
		char s[NUMBER];
		int w[NUMBER];
		int num;
		Stat(s, w, num, file_content);

		/*����ͳ�ƽ������*/
		HuffTree<char>* tree = HuffTree<char>::HuffmanBuild(s, w, num);

		/*���ļ����ݱ���*/
		unordered_map<char, std::string> encode_map;
		HuffTree<char>::storeHuffmanCode(tree->root(), encode_map);
		string encode_str = "";
		/*�����ļ������ַ�������ÿһ���ַ�ӳ��ɶ�Ӧ��huffman���룬������������ַ���*/
		for (char& x : file_content) {
			encode_str += encode_map.at(x);
		}

		/*���������Զ����Ʒ�ʽ����ָ���ļ�*/
		size_t find = file_path.find(".txt");
		string output_path = file_path.substr(0, find) + "_result.huf";

		if (FileProcess::writeBinaryContent(encode_str, output_path.c_str())) {
			printf("\n������ɣ��������Ѵ��룺%s\n\n", output_path.c_str());
		}

		/*ѹ���ʼ���*/
		int before_encode = file_content.length();
		double after_encode = ceil(encode_str.length() * 1.0 / 8);
		printf("\nѹ���ʼ��㣺\nѹ��ǰ��С��%d B\nѹ�����С��%.0f B\nѹ���ʣ�%.2f %%\n",
			before_encode, after_encode, after_encode * 100.0 / before_encode);

		/*����huffman�����ͷ��ڴ�*/
		delete tree;
	}
}
