# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("HuffmanDecoder-Cmake")

# 包含子项目。
add_subdirectory (main)
add_subdirectory (data-structure)
add_subdirectory (file-process)
add_subdirectory (statistics)
add_subdirectory (encode)
add_subdirectory (decode)


# 预处理器选项
add_definitions(-std=c++11)
add_definitions(_CRT_SECURE_NO_WARNINGS)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXGLAGS} -O3 -Wall")
