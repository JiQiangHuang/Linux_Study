aux_source_directory(. SRCS)
add_executable(tmms ${SRCS})
# 添加这一行，链接 base 库
target_link_libraries(tmms base)
install(TARGETS tmms RUNTIME DESTINATION sbin)