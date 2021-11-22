#include "statistics.h"

/*
* �����ַ�����ͳ��ÿһ���ַ��ĳ���Ƶ��
* s: ��¼���ֹ����ַ�
* w: ��¼�ַ����ֵ�Ƶ��
* num: ��¼���ֹ����ַ�����
* content: ����ͳ�Ƶ��ַ���
*/
void Stat(char* s, int* w, int& num, std::string content) {
	//��ʼ��,��s��w��ֵȫ����Ϊ0
	num = 0;
	for (int i = 0; i < NUMBER; i++) {
		w[i] = 0;
		s[i] = 0;
	}
	//��������,ͳ�Ƹ����ַ�Ƶ��
	for (int i = 0; i < content.length(); i++) {
		char ch = content[i];
		w[ch]++;
		s[ch] = ch;
	}
	//ͳ��Ƶ����Ϊ0���ַ�,ɾ��Ϊ0���ַ�
	for (int i = 0; i < NUMBER; i++) {
		if (w[i] != 0) {
			w[num] = w[i];
			s[num] = s[i];
			w[i] = 0;
			s[i] = 0;
			num++;
		}
	}
}