#pragma once
#include "../file-process/file-process.h"
#include "../data-structure/HuffTree.hpp"
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <string>
#define NUMBER 128

using namespace std;

namespace Encode {
	/*
	* 对指定文件编码并将编码结果输出到一个二进制文件（中级要求）的过程
	*/
	void encode_process();
}