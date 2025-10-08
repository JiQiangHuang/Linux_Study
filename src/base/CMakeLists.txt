# aux_source_directory(. DIR_LIB_SRCS)
# add_library (base ${DIR_LIB_SRCS})
# target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(. DIR_LIB_SRCS)

# 创建 base 库
add_library(base ${DIR_LIB_SRCS})

# 设置包含目录
target_include_directories(base 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# 添加依赖关系
add_dependencies(base jsoncpp)

# 链接 jsoncpp 库
target_link_libraries(base jsoncpp_static)

# 添加编译定义
target_compile_definitions(base PUBLIC _GLIBCXX_USE_CXX11_ABI=1)