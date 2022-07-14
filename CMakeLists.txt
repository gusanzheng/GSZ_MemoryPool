cmake_minimum_required(VERSION 3.16)
project(GSZ_MemoryPool)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

aux_source_directory(./src SOURCE)

add_executable(GSZ_MemoryPool ${SOURCE})

target_link_libraries(GSZ_MemoryPool pthread)


