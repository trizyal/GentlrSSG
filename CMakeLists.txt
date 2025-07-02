cmake_minimum_required(VERSION 3.31)
project(GentlrSSG)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(gentlr main.cpp)
target_link_libraries(gentlr PRIVATE gentlr_lib)
