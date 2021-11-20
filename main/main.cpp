// main.cpp
//

#include "main.h"
#include "../statistics/statistics.h"
#include "../encode/encode.h"

using namespace std;

void menu()
{
    
    bool exit_sig = false; // 程序退出的标志
    while (!exit_sig)
    {
        while (!_kbhit())
        {
            showMenu();
            Sleep(800);
        }

        switch (_getch())
        {
        case '1':
            Statistics::statistics_process();
            system("pause");
            break;
        case '2':
            Encode::encode_process();
            system("pause");
            break;
        case '3':
            cout << "3" << endl;
            system("pause");
            break;
        case '4':
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
        "\t[1]: 统计输入文件字符频度并对字符集编括码并输出至文件（基本要求）\n"
        "\t[2]: 对整个文件编括码并保存结果到一个二进制文件（中级要求）\n"
        "\t[3]: 文件解码并将解码结果保存为一文本文件（高级要求）\n"
        "\t[4]: 退出";
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