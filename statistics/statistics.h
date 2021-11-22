#pragma once

#include <iostream>
#include <string>
#define NUMBER 128
using namespace std;


//
// 统计输入文件字符频度并对字符集编码并输出至文件（基本要求）的过程
//
void statistics_process();

/*
* 遍历字符串来统计每一个字符的出现频度
* s: 记录出现过的字符
* w: 记录字符出现的频度
* num: 记录出现过的字符数量
* content: 用于统计的字符串
*/
void Stat(char* s, int* w, int& num, std::string content);
