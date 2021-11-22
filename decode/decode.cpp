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
	* 将01字符串解码为原来的字符串
	* binCode: 存储二进制信息的字符串，由0和1字符构成
	* map: 从二进制信息字符串到字符的映射表
	* num: 原文件中的字符总数
	*/
	string binToString(string binCode, unordered_map<string, char>& map, int num) {
		string code = "";
		string result = "";
		/*用类似于队列的方式处理binCode*/
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
	* 根据**_code.txt和**_result.huf的内容，解码出原始的文本文件并另存到磁盘**_reconstruct.txt的过程（高级要求）
	*/
	void decode_process()
	{
		static string file_path_code = ""; // **_code.txt文件路径
		static string file_path_result = ""; // **_result.huf文件路径
		int num_of_original_ch = 0; // 原文件中的字符数量
		unordered_map<string, char> decode_map; // 解码用的哈希表

		/*变量初始化阶段*/
		file_path_result = FileProcess::getFilePath("选择编码结果文件", BINARY_MODE); // 获取用户所选**_result.huf文件的路径
		int suffix_index = file_path_result.find("_result.huf"); // 字符串后缀名部分的下标，切割用
		file_path_code = file_path_result.substr(0, suffix_index) + "_code.txt";
		if (file_path_result.compare("NONE") == 0) {
			MessageBox(NULL, TEXT("没有选择二进制文件，无法解码"),
				NULL, MB_ICONERROR); // 弹出错误提示对话框
		}
		/*
		* 从**_code.txt中读取内容，初始化num_of_original_ch和decode_map
		* 如果没找到对应的**_code.txt，弹出错误提示对话框，并停止后续工作
		*/
		else if (!FileProcess::readEncodeResult(num_of_original_ch, decode_map, file_path_code.c_str())) {
			string error_message = "错误：没有找到\n" + file_path_code + 
				"\n无法解码，请在程序第1步得到统计结果后重试";
			MessageBox(NULL, TEXT(error_message.c_str()),
				NULL, MB_ICONERROR); // 弹出错误提示对话框
		}
		/*
		* 读取文件全部正常的情况下，进行解码步骤
		*/
		else {
			printf("%s", "\n读取二进制文件成功\n读取统计结果文件成功\n正在解码...\n");
			// 从**_result.huf中读取内容，存入字符串
			string encode_content = FileProcess::readBinaryContent(file_path_result.c_str());
			string ret = binToString(encode_content, decode_map, num_of_original_ch);
			string output_path = file_path_result.substr(0, suffix_index) + "_reconstruct.txt";
			if (FileProcess::writeTextContent(ret, output_path.c_str())) {
				cout << "\n解码完成，解码结果已写入：" << output_path << endl;
			}

		}


	}
}