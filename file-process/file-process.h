#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <commdlg.h>
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
	* return: string�����ַ������洢��ѡ�ļ���·�������û��ѡ���ļ���Ĭ�Ϸ���ֵΪ"FATALERROR"
	*/
	string getFilePath();

	bool writeBinaryContent(std::string content, const char* filename);
}
