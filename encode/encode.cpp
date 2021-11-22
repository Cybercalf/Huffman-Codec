#include "encode.h"

using namespace std;

namespace Encode {
	
    /*
    * 遍历字符串来统计每一个字符的出现频度
    * s: 记录出现过的字符
    * w: 记录字符出现的频度
    * num: 记录出现过的字符数量
    * content: 用于统计的字符串
    */
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

	void encode_process() {
        /* 从文件中获取信息存入一个字符串 */
        static string file_path = ""; // 存储文件路径
        static string file_content = ""; // 存储文件内容
        file_path = FileProcess::getFilePath("选择原文件", TEXT_MODE); // 获取用户所选文件的路径
        if (file_path.compare("NONE")==0) { // 如果用户没有选择文件
            MessageBox(NULL, TEXT("没有选择文本文件，无法编码"),
                NULL, MB_ICONERROR); // 弹出错误提示对话框
        }
        else { // 如果用户正常选择文件
            printf("\n选择文件：%s\n\n正在编码...\n", file_path.c_str());
            file_content = FileProcess::readTextContent(file_path.c_str()); // 读取文件中的全部内容，存入字符串

            /* 遍历字符串来统计每一个字符的出现频度 */
            char s[NUMBER];
            int w[NUMBER];
            int num;
            Stat(s, w, num, file_content);

            /*根据统计结果建树*/
            HuffTree<char>* tree = HuffTree<char>::HuffmanBuild(s, w, num);

            /*将文件内容编码*/
            unordered_map<char, std::string> encode_map;
            HuffTree<char>::storeHuffmanCode(tree->root(), encode_map);
            string encode_str = "";
            /*遍历文件内容字符串，把每一个字符映射成对应的huffman编码，存入编码内容字符串*/
            for (char& x : file_content) { 
                encode_str += encode_map.at(x);
            }

            /*将编码结果以二进制方式存入指定文件*/
            size_t find = file_path.find(".txt");
            string output_path = file_path.substr(0, find) + "_result.huf";

            if (FileProcess::writeBinaryContent(encode_str, output_path.c_str())) {
                printf("\n编码完成，编码结果已存入：%s\n\n", output_path.c_str());
            }

            /*压缩率计算*/
            int before_encode = file_content.length();
            double after_encode = ceil(encode_str.length() * 1.0 / 8);
            printf("\n压缩率计算：\n压缩前大小：%d B\n压缩后大小：%.0f B\n压缩率：%.2f %%\n",
                before_encode, after_encode, after_encode * 100.0 / before_encode);

            /*清理huffman树，释放内存*/
            delete tree;
        }
	}

}