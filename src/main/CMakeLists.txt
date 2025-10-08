# aux_source_directory(. SRCS)
# add_executable(tmms ${SRCS})

# # 添加这一行，链接 base 库
# add_dependencies(base jsoncpp)
# target_link_libraries(tmms base jsoncpp_static.a)

# install(TARGETS tmms RUNTIME DESTINATION sbin)

aux_source_directory(. SRCS)

# 创建可执行文件
add_executable(tmms ${SRCS})

# 正确的依赖关系
add_dependencies(tmms base)

# 链接库
target_link_libraries(tmms 
    base 
    jsoncpp_static
    pthread
    rt
)

install(TARGETS tmms RUNTIME DESTINATION bin)