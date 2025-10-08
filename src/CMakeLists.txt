# 添加包含目录（让所有子目录都能访问 base 头文件）
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 按正确顺序添加子目录
add_subdirectory(base)
add_subdirectory(network/base)  # 添加 network/base 目录
add_subdirectory(main)