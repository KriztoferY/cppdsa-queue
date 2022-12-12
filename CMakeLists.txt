# 3.12: support for C++20
# 3.15: generator expressions
cmake_minimum_required(VERSION 3.15) 

project(cppdsa-queue VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_DEBUG_POSTFIX d)
configure_file(ProjectConfig.h.in ProjectConfig.h)

add_library(project_compiler_flags INTERFACE)
target_compile_features(project_compiler_flags INTERFACE cxx_std_20)

# Add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(project_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# if(APPLE)
#   set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
# elseif(UNIX)
#   set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
# endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# === make install ===
set(APP_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(APP_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(APP_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

enable_testing()    # CAVEAT: must be in top-level CMakeLists.txt

# === header dir ===
set(QUEUE_HEADER_DIR ${PROJECT_SOURCE_DIR}/src/queue)

add_subdirectory(src)       # shared library
add_subdirectory(test)      # tests
# add_subdirectory(benchmark)
