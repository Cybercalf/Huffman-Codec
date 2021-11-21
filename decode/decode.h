#pragma once
#include "../file-process/file-process.h"
#include <iostream>
#include <string>
#define NUMBER 128

using namespace std;

namespace Decode {
	/*
	* 根据**_code.txt和**_result.huf的内容，解码出原始的文本文件并另存到磁盘**_reconstruct.txt的过程（高级要求）
	*/
	void decode_process();
}