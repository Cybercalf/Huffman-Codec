#include "file-process.h"

namespace FileProcess {
	string readTextContent(const char* filepath)
	{
		FILE* infile = fopen(filepath, "r");
		string str = "";
		char ch = '\0';
		if (infile != NULL)
		{
			while (!feof(infile))
			{
				if (fscanf(infile, "%c", &ch) == 1)
				{
					str += ch;
				}
			}
			fclose(infile);
		}
		return str;
	}

	string getFilePath()
	{
		OPENFILENAME ofn = { 0 };
		TCHAR strFileName[MAX_PATH] = { 0 };									  //用于接收文件名
		ofn.lStructSize = sizeof(OPENFILENAME);								  //结构体大小
		ofn.hwndOwner = NULL;												  //拥有者窗口句柄
		ofn.nFilterIndex = 1;												  //过滤器索引
		ofn.lpstrFile = strFileName;										  //接收返回的文件名，注意第一个字符需要为NULL
		ofn.nMaxFile = sizeof(strFileName);									  //缓冲区长度
		ofn.lpstrInitialDir = NULL;											  //初始目录为默认
		ofn.lpstrTitle = TEXT("选择文件");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //文件、目录必须存在，隐藏只读选项
		//打开文件对话框
		string filePath = "FATALERROR";
		if (GetOpenFileName(&ofn))
		{
			filePath = (string)strFileName;
		}
		return filePath;
	}

	bool writeTextContent(string content, const char* filename) {
		FILE* outfile = fopen(filename, "w");
		if (outfile != NULL) {
			fprintf(outfile, "%s", content.c_str());
			fclose(outfile);
			return true;
		}
		else {
			return false;
		}
	}

	int binStringToInt(string hex)
	{
		return stoi(hex, nullptr, 2);
	}

	bool writeBinaryContent(std::string content, const char* filename)
	{
		FILE* outfile;
		if ((outfile = fopen(filename, "wb")) == NULL)
		{
			return false;
		}
		else
		{
			// 补齐八位
			while (content.length() % 8 != 0)
			{
				content += "0";
			}
			// 转为二进制数存入文档
			while (!content.empty())
			{
				unsigned char ch = binStringToInt(content.substr(0, 8));
				fwrite(&ch, 1, 1, outfile);
				content = content.substr(8);
			}
			fclose(outfile);
			return true;
		}
	}

	///*
	//Function:        TCHAR2STRING
	//Description:     TCHAR转string
	//Input:           str:待转化的TCHAR*类型字符串
	//Return:          转化后的string类型字符串
	//相关函数：getFilePath
	//*/
	//string TCHAR2STRING(TCHAR* str)
	//{
	//	std::string ret = "";
	//	try
	//	{
	//		int iLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)str, -1, NULL, 0, NULL, NULL); // 用于确定字符的数量?
	//
	//		char* chRtn = new char[iLen * sizeof(char)]; // 根据上一句开辟相应大小的空间
	//
	//		WideCharToMultiByte(CP_ACP, 0, (LPCWCH)str, -1, chRtn, iLen, NULL, NULL); // 把转化后的内容存在字符串chRtn里
	//
	//		ret = chRtn;
	//	}
	//	catch (exception e)
	//	{
	//	}
	//	return ret;
	//}
}

