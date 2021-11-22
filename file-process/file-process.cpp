#include "file-process.h"


namespace FileProcess {

	string getFilePath(const char* title, int filter_mode)
		{
			OPENFILENAME ofn = { 0 };
			TCHAR strFileName[MAX_PATH] = { 0 };									  //用于接收文件名
			ofn.lStructSize = sizeof(OPENFILENAME);								  //结构体大小
			ofn.hwndOwner = NULL;												  //拥有者窗口句柄
			ofn.lpstrFile = strFileName;										  //接收返回的文件名，注意第一个字符需要为NULL
			ofn.nMaxFile = sizeof(strFileName);									  //缓冲区长度
			ofn.lpstrInitialDir = NULL;											  //初始目录为默认
			ofn.lpstrTitle = TEXT(title); // 对话框标题
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //文件、目录必须存在，隐藏只读选项
			ofn.lpstrFilter = TEXT("文本文件(*.txt)\0*.txt\0二进制文件(*.huf)\0*.huf\0所有文件(*.*)\0*.*\0\0"); //文件选择过滤器
			ofn.nFilterIndex = filter_mode;												  //过滤器索引

			//打开文件对话框
			string filePath = "NONE"; // 字符串默认值为NONE
			if (GetOpenFileName(&ofn)) // 若文件正常打开，返回得到的文件路径
			{
				filePath = (string)strFileName;
			}
			return filePath;
		}

	string readTextContent(const char* filepath)
	{
		/*以文本只读方式打开文件*/
		FILE* infile = fopen(filepath, "r");
		string str = "";
		char ch = '\0';
		/*若正常打开文件，则遍历文件内容并记录*/
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

	bool readEncodeResult(int& num_of_file_ch, unordered_map<string, char>& decode_map,
		const char* filepath) {

		ifstream infile;
		string binstr = "", chstr = "";
		infile.open(filepath, ios::in);
		// 若文件正常打开
		if (infile) {
			infile >> num_of_file_ch;
			if (num_of_file_ch != 0) {
				while (!infile.eof()) {
					infile >> chstr >> binstr;
					if (chstr.compare("<space>") == 0) {
						decode_map.insert({ binstr, ' ' });
					}
					else if (chstr.compare("\\n") == 0) {
						decode_map.insert({ binstr, '\n' });
					}
					else if (chstr.compare("\\t") == 0) {
						decode_map.insert({ binstr, '\t' });
					}
					else {
						decode_map.insert({ binstr, chstr.at(0) });
					}
				}
			}
			infile.close();
			return true;
		}
		// 若文件未正常打开
		else {
			return false;
		}
	}

	/*
	* 将长度为8的二进制信息字符串转为相应的整数
	* hex: 二进制信息字符串，由0和1字符构成，长度为8
	*/
	int binStringToInt(string hex)
	{
		return stoi(hex, nullptr, 2);
	}

	/*
	* 将一字节大小的信息转为长度为8的二进制信息字符串
	* ch: 一字节大小的二进制信息
	* return: 二进制信息字符串，由0和1字符构成，长度为8
	*/
	string intToBinString(unsigned char ch)
	{
		string ret = "";
		unsigned int num = ch;

		// 字符串的长度是8位
		while (ret.length() < 8) {
			ret = to_string(num % 2) + ret;
			num = num >> 1;
		}
		return ret;
	}

	string readBinaryContent(const char* filepath)
	{
		string ret = "";
		unsigned char ch = '\0';
		ifstream infile;
		infile.open(filepath, ios::in | ios::binary);
		while (infile.read((char*)&ch, sizeof(ch))) {
			ret += intToBinString(ch);
		}

		return ret;
	}

	bool writeBinaryContent(std::string binary_content, const char* filepath)
	{
		FILE* outfile;
		if ((outfile = fopen(filepath, "wb")) == NULL)
		{
			return false;
		}
		else
		{
			// 补齐八位
			while (binary_content.length() % 8 != 0)
			{
				binary_content += "0";
			}
			// 转为二进制数存入文档
			while (!binary_content.empty())
			{
				unsigned char ch = binStringToInt(binary_content.substr(0, 8));
				fwrite(&ch, 1, 1, outfile);
				binary_content = binary_content.substr(8);
			}
			fclose(outfile);
			return true;
		}
	}
}

