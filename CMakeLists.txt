cmake_minimum_required(VERSION 3.31)
project(GentlrSSG)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(gentlr main.cpp)
target_include_directories(
        gentlr_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(gentlr PRIVATE gentlr_lib)
