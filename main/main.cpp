// main.cpp: 程序入口点和main()所在位置
//

#include "main.h"
#include "../statistics/statistics.h"
#include "../encode/encode.h"
#include "../decode/decode.h"

using namespace std;

void menu()
{
    bool exit_sig = false; // 程序退出的标志
    /*开始循环*/
    while (!exit_sig)
    {
        /*等待用户按键*/
        while (!_kbhit())
        {
            showMenu();
            Sleep(800);
        }
        /*根据用户按键决定调用的函数*/
        switch (_getch())
        {
        case '1':
            statistics_process();
            system("pause");
            break;
        case '2':
            encode_process();
            system("pause");
            break;
        case '3':
            decode_process();
            system("pause");
            break;
        case '4':
            printf("%s\n", "Goodbye!");
            system("pause");
            exit_sig = true;
            break;
        default:
            break;
        }
    }
}

void showMenu()
{
    static char show_menu_str[] =
        "\n\n\n"
        "\tHuffman编码器\n"
        "\t操作命令说明：\n"
        "\t[1]: 统计输入文件字符频度并对字符集编码并输出至文件（基本要求）\n"
        "\t[2]: 对整个文件编码并保存结果到一个二进制文件（中级要求）\n"
        "\t[3]: 文件解码并将解码结果保存为一文本文件（高级要求）\n"
        "\t[4]: 退出\n\n"
        "\t注意：第3步解码操作需要同时用到第1步得到的统计结果文件，与第2步得到的编码结果文件\n";
    system("cls");
    printf("%s\n", show_menu_str);
}

int main()
{
    menu();
}

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目