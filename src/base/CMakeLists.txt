aux_source_directory(. DIR_LIB_SRCS)
add_library (base ${DIR_LIB_SRCS})
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})