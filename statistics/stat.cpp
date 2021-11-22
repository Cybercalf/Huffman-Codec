#include "statistics.h"

/*
* 遍历字符串来统计每一个字符的出现频度
* s: 记录出现过的字符
* w: 记录字符出现的频度
* num: 记录出现过的字符数量
* content: 用于统计的字符串
*/
void Stat(char* s, int* w, int& num, std::string content) {
	//初始化,将s与w的值全部置为0
	num = 0;
	for (int i = 0; i < NUMBER; i++) {
		w[i] = 0;
		s[i] = 0;
	}
	//遍历内容,统计各个字符频度
	for (int i = 0; i < content.length(); i++) {
		char ch = content[i];
		w[ch]++;
		s[ch] = ch;
	}
	//统计频数不为0的字符,删除为0的字符
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