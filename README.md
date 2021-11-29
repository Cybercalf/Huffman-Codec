# Huffman-Codec

基于Huffman编码的简易文本文件编解码器，适用于Windows 64位平台

### 使用

适用平台：Windows 64位操作系统

类型：控制台应用

各模式说明：

1. 统计模式：选择需要编码的文本文件（如t1.txt），程序将统计结果输出到控制台并存于另一文本文件（如t1_code.txt）中
2. 编码模式：再次选择原文件（t1.txt），程序将编码结果存于二进制文件（如t1_result.huf）中
3. 解码模式：选择二进制文件（t1_result.huf），如果文件夹中同时存在统计结果文件（t1_code.txt），程序将解码结果存于另一文本文件（如t1_reconstruct.txt）中

### 构建

编程语言：C/C++

项目构建工具：CMake, Visual Studio 2022

### 背景

本项目为四川大学2021-2022学年秋数据结构与算法课程第二个实验的小组成果，验收完成于2021年11月29日上午10:30-11:00。

### 鸣谢

项目绝大部分工作由[李郭华](https://github.com/White-Prostitute)和[胡未名](https://github.com/Cybercalf)共同完成，[陈怡君](https://github.com/dobole)负责了win32 API函数调用相关代码的编写，同时感谢[马扬](mailto:379051737@qq.com)在二进制文件读写方面提供思路上的帮助。

4人全部来自[四川大学](https://scu.edu.cn/index.htm)[软件学院](https://sw.scu.edu.cn/)2020级。

### 其他

1. 项目文档位于`doc`文件夹中
2. 项目仅供学习交流使用，请遵循[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)协议
