# 让指定文件夹下的头文件能被这个文件夹下的程序找到
# include_directories(${PROJECT_SOURCE_DIR}/data-structure)
# 将生成的二进制链接库文件放到使用cmake文件夹下的lib文件夹中
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 给该目录下的所有源文件起一个别名
aux_source_directory(./ DIR_LIB_SRCS)
# 将该目录下的所有源文件在生成二进制链接库文件时被使用
add_library(statistics ${DIR_LIB_SRCS})

target_compile_options(statistics PRIVATE -fexec-charset=GBK)