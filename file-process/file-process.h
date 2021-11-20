#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <commdlg.h>
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
	* return: string类型字符串，存储所选文件的路径；如果没有选择文件，默认返回值为"FATALERROR"
	*/
	string getFilePath();

	bool writeBinaryContent(std::string content, const char* filename);
}
