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
	// 以文本形式获取指定文件的全部内容
	// filepath: 指定的文件路径
	// return: 存储文件中全部内容的string类型字符串
	//
	string readTextContent(const char* filepath);

	/*
	* 以文本形式将一个字符串的内容输出到指定文件
	* content: 存储内容的字符串
	* filename: 文件名
	* return: 成功返回true，失败返回false
	*/
	bool writeTextContent(string content, const char* filename);


	/*
	* 利用Win32API获取所选文件的路径
	* title: 对话框头部标题，用于提示用户
	* filter_mode: 选择筛选文本文件还是二进制文件
	* return: string类型字符串，存储所选文件的路径；如果没有选择文件，默认返回值为"FATALERROR"
	*/
	string getFilePath(const char * title, int filter_mode);

	/*
	* 将编码结果以二进制形式写入"**_result.huf"
	* binary_content: 编码结果字符串，全部由0和1字符构成
	* filepath: 要存入内容的二进制文件路径
	* return: 成功返回true，失败返回false
	*/
	bool writeBinaryContent(std::string binary_content, const char* filepath);

	/*
	* 从 "**_code.txt" 中读取统计信息，存入相应变量
	* num_of_file_ch: 存储原文件字符总数的buffer
	* decode_map: 解码用的映射表
	* filepath: 要打开的文件路径
	* return: 打开文件成功返回true，失败返回false；
	*/
	bool readEncodeResult(int& num_of_file_ch, unordered_map<string, char>& decode_map, 
		const char* filepath);

	string readBinaryContent(const char* filepath);
}
