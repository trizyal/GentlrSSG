add_subdirectory(external/md4c)

file(GLOB SRC_FILES "*.cpp")
add_library(gentlr_lib ${SRC_FILES})
target_include_directories(
        gentlr_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(gentlr_lib PUBLIC md4c md4c-html)