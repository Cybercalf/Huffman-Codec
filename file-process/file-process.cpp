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
		TCHAR strFileName[MAX_PATH] = { 0 };									  //���ڽ����ļ���
		ofn.lStructSize = sizeof(OPENFILENAME);								  //�ṹ���С
		ofn.hwndOwner = NULL;												  //ӵ���ߴ��ھ��
		ofn.nFilterIndex = 1;												  //����������
		ofn.lpstrFile = strFileName;										  //���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL
		ofn.nMaxFile = sizeof(strFileName);									  //����������
		ofn.lpstrInitialDir = NULL;											  //��ʼĿ¼ΪĬ��
		ofn.lpstrTitle = TEXT("ѡ���ļ�");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //�ļ���Ŀ¼������ڣ�����ֻ��ѡ��
		//���ļ��Ի���
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
			// �����λ
			while (content.length() % 8 != 0)
			{
				content += "0";
			}
			// תΪ�������������ĵ�
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
	//Description:     TCHARתstring
	//Input:           str:��ת����TCHAR*�����ַ���
	//Return:          ת�����string�����ַ���
	//��غ�����getFilePath
	//*/
	//string TCHAR2STRING(TCHAR* str)
	//{
	//	std::string ret = "";
	//	try
	//	{
	//		int iLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)str, -1, NULL, 0, NULL, NULL); // ����ȷ���ַ�������?
	//
	//		char* chRtn = new char[iLen * sizeof(char)]; // ������һ�俪����Ӧ��С�Ŀռ�
	//
	//		WideCharToMultiByte(CP_ACP, 0, (LPCWCH)str, -1, chRtn, iLen, NULL, NULL); // ��ת��������ݴ����ַ���chRtn��
	//
	//		ret = chRtn;
	//	}
	//	catch (exception e)
	//	{
	//	}
	//	return ret;
	//}
}

