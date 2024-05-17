cmake_minimum_required(VERSION 3.29)
project (main)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (src SRC_LIST)

include_directories (inc)

add_executable (main ${SRC_LIST})