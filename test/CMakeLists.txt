cmake_minimum_required(VERSION 3.12)
project(strplay_tests)

add_subdirectory(lib/googletest)

include_directories(${STR_UTILS_HEADER_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/str_utils/str_utils_test.cpp)

add_executable(strplay_tests ${SOURCE_FILES})
target_link_libraries(strplay_tests strutils gtest)
install(TARGETS strplay_tests DESTINATION bin)