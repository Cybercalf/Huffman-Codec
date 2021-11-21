# CMakeList.txt: HuffmanDecoder-Cmake 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 让生成的二进制可执行文件放到使用cmake的目录下的bin文件夹中
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# 给该目录下的所有源文件起一个别名
aux_source_directory(./ DIR_SRCS)
# 将该目录下的所有源文件在生成二进制可执行文件时被使用
add_executable(main ${DIR_SRCS})
# 将用到的链接库添加进来
target_link_libraries(main data-structure)
target_link_libraries(main file-process)
target_link_libraries(main statistics)
target_link_libraries(main encode)
target_link_libraries(main decode)

target_compile_options(main PRIVATE -fexec-charset=GBK)

# TODO: 如有需要，请添加测试并安装目标。
