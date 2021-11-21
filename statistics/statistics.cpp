#include "statistics.h"
#include "../data-structure/HuffTree.hpp"

#define NUMBER 128

namespace Statistics
{
    /* �����ַ�����ͳ��ÿһ���ַ��ĳ���Ƶ�� */
    void Stat(char* s, int* w, int& num, string context) {
        //��ʼ��
        num = 0;
        for (int i = 0; i < NUMBER; i++) {
            w[i] = 0;
            s[i] = 0;
        }
        //��������,ͳ��Ƶ��
        for (int i = 0; i < context.length(); i++) {
            char ch = context[i];
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

    void statistics_process()
    {
        /* ���ļ��л�ȡ��Ϣ����һ���ַ��� */
	    static string file_path = ""; // �洢�ļ�·�����ַ���
	    static string file_content = ""; // �洢�ļ����ݵ��ַ���
        file_path = FileProcess::getFilePath("ѡ��ԭ�ļ�", TEXT_MODE); // �û�ѡ���ļ�����ȡѡ���ļ���·��
        if (file_path.compare("NONE")==0) { // ����û�û��ѡ���ļ�
            MessageBox(NULL, TEXT("û��ѡ���ı��ļ����޷�ͳ��"),
                NULL, MB_ICONERROR); // ����������ʾ�Ի���
        }
        else { // ����û�����ѡ���ļ�
            printf("\nѡ���ļ���%s\n\n", file_path.c_str());
            file_content = FileProcess::readTextContent(file_path.c_str()); // ��ȡ�ļ��е�ȫ�����ݣ������ַ���

            /* �����ַ�����ͳ��ÿһ���ַ��ĳ���Ƶ�� */
            char s[NUMBER];
            int w[NUMBER];
            int num;
            Stat(s, w, num, file_content);


            /*����ͳ�ƽ������*/
            HuffTree<char>* tree = HuffTree<char>::HuffmanBuild<char>(s, w, num);

            /*����������ͳ�ƽ������ӡ������̨*/
            printf("%s", "ͳ�ƽ����\n�ַ�\tƵ��\t��Ӧ����\n");
            HuffTree<char>::printHuffmanCode<char>(tree->root(), "");

            /*�����ɵ�ͳ�ƽ�����ı���ʽ����ָ���ļ�*/
            string stat_result = to_string(file_content.length()) + "\n"; // �ȴ�ԭ�ļ����ַ�����
            stat_result += HuffTree<char>::huffmanCode(tree->root(), "");
            size_t find = file_path.find(".txt");
            string output_path = file_path.substr(0, find) + "_code.txt";
            if (FileProcess::writeTextContent(stat_result, output_path.c_str())) {
                printf("\nͳ����ɣ�ͳ�ƽ���Ѵ��룺%s\n\n", output_path.c_str());
            }
        }
    }
}
