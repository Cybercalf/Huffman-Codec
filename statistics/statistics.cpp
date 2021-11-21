#include "statistics.h"
#include "../data-structure/HuffTree.hpp"

#define NUMBER 128

namespace Statistics
{
    /* 遍历字符串来统计每一个字符的出现频度 */
    void Stat(char* s, int* w, int& num, string context) {
        //初始化
        num = 0;
        for (int i = 0; i < NUMBER; i++) {
            w[i] = 0;
            s[i] = 0;
        }
        //遍历内容,统计频度
        for (int i = 0; i < context.length(); i++) {
            char ch = context[i];
            w[ch]++;
            s[ch] = ch;
        }
        //统计频数不为0的字符,删除为0的字符
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
        /* 从文件中获取信息存入一个字符串 */
	    static string file_path = ""; // 存储文件路径的字符串
	    static string file_content = ""; // 存储文件内容的字符串
        file_path = FileProcess::getFilePath("选择原文件", TEXT_MODE); // 用户选择文件，获取选择文件的路径
        if (file_path.compare("NONE")==0) { // 如果用户没有选择文件
            MessageBox(NULL, TEXT("没有选择文本文件，无法统计"),
                NULL, MB_ICONERROR); // 弹出错误提示对话框
        }
        else { // 如果用户正常选择文件
            printf("\n选择文件：%s\n\n", file_path.c_str());
            file_content = FileProcess::readTextContent(file_path.c_str()); // 读取文件中的全部内容，存入字符串

            /* 遍历字符串来统计每一个字符的出现频度 */
            char s[NUMBER];
            int w[NUMBER];
            int num;
            Stat(s, w, num, file_content);


            /*根据统计结果建树*/
            HuffTree<char>* tree = HuffTree<char>::HuffmanBuild<char>(s, w, num);

            /*根据树生成统计结果并打印到控制台*/
            printf("%s", "统计结果：\n字符\t频度\t对应编码\n");
            HuffTree<char>::printHuffmanCode<char>(tree->root(), "");

            /*将生成的统计结果以文本形式存入指定文件*/
            string stat_result = to_string(file_content.length()) + "\n"; // 先存原文件的字符数量
            stat_result += HuffTree<char>::huffmanCode(tree->root(), "");
            size_t find = file_path.find(".txt");
            string output_path = file_path.substr(0, find) + "_code.txt";
            if (FileProcess::writeTextContent(stat_result, output_path.c_str())) {
                printf("\n统计完成，统计结果已存入：%s\n\n", output_path.c_str());
            }
        }
    }
}
