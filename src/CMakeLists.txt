cmake_minimum_required(VERSION 3.12)
project(strplay) # main app of the project

add_subdirectory(str_utils)
set(SOURCE_FILES main.cpp)

add_executable(strplay ${SOURCE_FILES})
target_link_libraries(strplay strutils)
install(TARGETS strplay DESTINATION ${APP_INSTALL_BIN_DIR})