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
        file_path = FileProcess::getFilePath(); // �û�ѡ���ļ�����ȡѡ���ļ���·��
        if (file_path.compare("FATALERROR")==0) { // ����û�û��ѡ���ļ�
            MessageBox(NULL, TEXT("û��ѡ���ļ�"),
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

            /*���������ɱ��벢��ӡ������̨*/
            printf("%s", "ͳ�ƽ����\n�ַ�\tƵ��\t��Ӧ����\n");
            HuffTree<char>::printHuffmanCode<char>(tree->root(), "");

            /*�����ɵı��������ı���ʽ����ָ���ļ�*/
            string stat_result = HuffTree<char>::huffmanCode(tree->root(), "");
            size_t find = file_path.find(".txt");
            file_path = file_path.substr(0, find) + "_code.txt";
            if (FileProcess::writeTextContent(stat_result, file_path.c_str())) {
                printf("\n�������ѳɹ����룺%s\n\n", file_path.c_str());
            }
        }
    }
}
