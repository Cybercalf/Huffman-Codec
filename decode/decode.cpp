#pragma once
#include "decode.h"
#include <unordered_map>
#include "../file-process/file-process.h"
#include <iostream>
#include <string>
#define NUMBER 128

using namespace std;

namespace Decode {


	/*
	* ��01�ַ�������Ϊԭ�����ַ���
	* binCode: �洢��������Ϣ���ַ�������0��1�ַ�����
	* map: �Ӷ�������Ϣ�ַ������ַ���ӳ���
	* num: ԭ�ļ��е��ַ�����
	*/
	string binToString(string binCode, unordered_map<string, char>& map, int num) {
		string code = "";
		string result = "";
		/*�������ڶ��еķ�ʽ����binCode*/
		for (int i = 0; (num > 0) && (i < binCode.length()); i++) {
			code += binCode[i];
			try {
				result += map.at(code);
				num--;
				code = "";
			}
			catch (out_of_range e) {
				continue;
			}
		}
		return result;
	}


	/*
	* ����**_code.txt��**_result.huf�����ݣ������ԭʼ���ı��ļ�����浽����**_reconstruct.txt�Ĺ��̣��߼�Ҫ��
	*/
	void decode_process()
	{
		static string file_path_code = ""; // **_code.txt�ļ�·��
		static string file_path_result = ""; // **_result.huf�ļ�·��
		int num_of_original_ch = 0; // ԭ�ļ��е��ַ�����
		unordered_map<string, char> decode_map; // �����õĹ�ϣ��

		/*������ʼ���׶�*/
		file_path_result = FileProcess::getFilePath("ѡ��������ļ�", BINARY_MODE); // ��ȡ�û���ѡ**_result.huf�ļ���·��
		int suffix_index = file_path_result.find("_result.huf"); // �ַ�����׺�����ֵ��±꣬�и���
		file_path_code = file_path_result.substr(0, suffix_index) + "_code.txt";
		if (file_path_result.compare("NONE") == 0) {
			MessageBox(NULL, TEXT("û��ѡ��������ļ����޷�����"),
				NULL, MB_ICONERROR); // ����������ʾ�Ի���
		}
		/*
		* ��**_code.txt�ж�ȡ���ݣ���ʼ��num_of_original_ch��decode_map
		* ���û�ҵ���Ӧ��**_code.txt������������ʾ�Ի��򣬲�ֹͣ��������
		*/
		else if (!FileProcess::readEncodeResult(num_of_original_ch, decode_map, file_path_code.c_str())) {
			string error_message = "����û���ҵ�\n" + file_path_code + 
				"\n�޷����룬���ڳ����1���õ�ͳ�ƽ��������";
			MessageBox(NULL, TEXT(error_message.c_str()),
				NULL, MB_ICONERROR); // ����������ʾ�Ի���
		}
		/*
		* ��ȡ�ļ�ȫ������������£����н��벽��
		*/
		else {
			printf("%s", "\n��ȡ�������ļ��ɹ�\n��ȡͳ�ƽ���ļ��ɹ�\n���ڽ���...\n");
			// ��**_result.huf�ж�ȡ���ݣ������ַ���
			string encode_content = FileProcess::readBinaryContent(file_path_result.c_str());
			string ret = binToString(encode_content, decode_map, num_of_original_ch);
			string output_path = file_path_result.substr(0, suffix_index) + "_reconstruct.txt";
			if (FileProcess::writeTextContent(ret, output_path.c_str())) {
				cout << "\n������ɣ���������д�룺" << output_path << endl;
			}

		}


	}
}