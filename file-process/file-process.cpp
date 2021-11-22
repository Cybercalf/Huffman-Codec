#include "file-process.h"


namespace FileProcess {

	string getFilePath(const char* title, int filter_mode)
		{
			OPENFILENAME ofn = { 0 };
			TCHAR strFileName[MAX_PATH] = { 0 };									  //���ڽ����ļ���
			ofn.lStructSize = sizeof(OPENFILENAME);								  //�ṹ���С
			ofn.hwndOwner = NULL;												  //ӵ���ߴ��ھ��
			ofn.lpstrFile = strFileName;										  //���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL
			ofn.nMaxFile = sizeof(strFileName);									  //����������
			ofn.lpstrInitialDir = NULL;											  //��ʼĿ¼ΪĬ��
			ofn.lpstrTitle = TEXT(title); // �Ի������
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //�ļ���Ŀ¼������ڣ�����ֻ��ѡ��
			ofn.lpstrFilter = TEXT("�ı��ļ�(*.txt)\0*.txt\0�������ļ�(*.huf)\0*.huf\0�����ļ�(*.*)\0*.*\0\0"); //�ļ�ѡ�������
			ofn.nFilterIndex = filter_mode;												  //����������

			//���ļ��Ի���
			string filePath = "NONE"; // �ַ���Ĭ��ֵΪNONE
			if (GetOpenFileName(&ofn)) // ���ļ������򿪣����صõ����ļ�·��
			{
				filePath = (string)strFileName;
			}
			return filePath;
		}

	string readTextContent(const char* filepath)
	{
		/*���ı�ֻ����ʽ���ļ�*/
		FILE* infile = fopen(filepath, "r");
		string str = "";
		char ch = '\0';
		/*���������ļ���������ļ����ݲ���¼*/
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
		// ���ļ�������
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
		// ���ļ�δ������
		else {
			return false;
		}
	}

	/*
	* ������Ϊ8�Ķ�������Ϣ�ַ���תΪ��Ӧ������
	* hex: ��������Ϣ�ַ�������0��1�ַ����ɣ�����Ϊ8
	*/
	int binStringToInt(string hex)
	{
		return stoi(hex, nullptr, 2);
	}

	/*
	* ��һ�ֽڴ�С����ϢתΪ����Ϊ8�Ķ�������Ϣ�ַ���
	* ch: һ�ֽڴ�С�Ķ�������Ϣ
	* return: ��������Ϣ�ַ�������0��1�ַ����ɣ�����Ϊ8
	*/
	string intToBinString(unsigned char ch)
	{
		string ret = "";
		unsigned int num = ch;

		// �ַ����ĳ�����8λ
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
			// �����λ
			while (binary_content.length() % 8 != 0)
			{
				binary_content += "0";
			}
			// תΪ�������������ĵ�
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

