#pragma once

#include <iostream>
#include <string>
#define NUMBER 128
using namespace std;


//
// ͳ�������ļ��ַ�Ƶ�Ȳ����ַ������벢������ļ�������Ҫ�󣩵Ĺ���
//
void statistics_process();

/*
* �����ַ�����ͳ��ÿһ���ַ��ĳ���Ƶ��
* s: ��¼���ֹ����ַ�
* w: ��¼�ַ����ֵ�Ƶ��
* num: ��¼���ֹ����ַ�����
* content: ����ͳ�Ƶ��ַ���
*/
void Stat(char* s, int* w, int& num, std::string content);
