file(GLOB SRC_FILES "*.cpp")

add_library(gentlr_lib ${SRC_FILES})

target_include_directories(gentlr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
