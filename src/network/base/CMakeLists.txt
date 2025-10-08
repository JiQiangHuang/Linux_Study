# network/base 目录的 CMakeLists.txt
aux_source_directory(. NETWORK_BASE_SRCS)

# 创建网络基础库（如果需要的话）
# add_library(network_base ${NETWORK_BASE_SRCS})
# target_link_libraries(network_base base)
# target_include_directories(network_base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})