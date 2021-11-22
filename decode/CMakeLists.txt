include_directories(${PROJECT_SOURCE_DIR}/file-process)

# 将生成的二进制链接库文件放到使用cmake文件夹下的lib文件夹中
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 给该目录下的所有源文件起一个别名
aux_source_directory(./ DIR_LIB_SRCS)
# 将该目录下的所有源文件在生成二进制链接库文件时被使用
add_library(decode ${DIR_LIB_SRCS})

target_link_libraries(decode file-process)

target_compile_options(decode PRIVATE -finput-charset=GBK)
target_compile_options(decode PRIVATE -fexec-charset=GBK)