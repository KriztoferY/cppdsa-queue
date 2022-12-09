# REF:
# https://github.com/kigster/cmake-project-template

cmake_minimum_required(VERSION 3.12) # with support for C++20

project(strplay VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -g -Og")
# set(CMAKE_CXX_EXTENSIONS YES)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# === make install ===
set(APP_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(APP_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(APP_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# === header dir ===
set(STR_UTILS_HEADER_DIR ${PROJECT_SOURCE_DIR}/src/str_utils)

include_directories(${APP_INSTALL_INCLUDE_DIR})
include_directories(${STR_UTILS_HEADER_DIR})

add_subdirectory(src)
add_subdirectory(test)
# add_subdirectory(benchmark)
