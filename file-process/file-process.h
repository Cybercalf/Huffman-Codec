#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <commdlg.h>
#include <unordered_map>
#define TEXT_MODE 1
#define BINARY_MODE 2
using namespace std;

namespace FileProcess{

	// 
	// ���ı���ʽ��ȡָ���ļ���ȫ������
	// filepath: ָ�����ļ�·��
	// return: �洢�ļ���ȫ�����ݵ�string�����ַ���
	//
	string readTextContent(const char* filepath);

	/*
	* ���ı���ʽ��һ���ַ��������������ָ���ļ�
	* content: �洢���ݵ��ַ���
	* filename: �ļ���
	* return: �ɹ�����true��ʧ�ܷ���false
	*/
	bool writeTextContent(string content, const char* filename);


	/*
	* ����Win32API��ȡ��ѡ�ļ���·��
	* title: �Ի���ͷ�����⣬������ʾ�û�
	* filter_mode: ѡ��ɸѡ�ı��ļ����Ƕ������ļ�
	* return: string�����ַ������洢��ѡ�ļ���·�������û��ѡ���ļ���Ĭ�Ϸ���ֵΪ"FATALERROR"
	*/
	string getFilePath(const char * title, int filter_mode);

	/*
	* ���������Զ�������ʽд��"**_result.huf"
	* binary_content: �������ַ�����ȫ����0��1�ַ�����
	* filepath: Ҫ�������ݵĶ������ļ�·��
	* return: �ɹ�����true��ʧ�ܷ���false
	*/
	bool writeBinaryContent(std::string binary_content, const char* filepath);

	/*
	* �� "**_code.txt" �ж�ȡͳ����Ϣ��������Ӧ����
	* num_of_file_ch: �洢ԭ�ļ��ַ�������buffer
	* decode_map: �����õ�ӳ���
	* filepath: Ҫ�򿪵��ļ�·��
	* return: ���ļ��ɹ�����true��ʧ�ܷ���false��
	*/
	bool readEncodeResult(int& num_of_file_ch, unordered_map<string, char>& decode_map, 
		const char* filepath);

	string readBinaryContent(const char* filepath);
}
