# include(FetchContent)
# FetchContent_Declare(
# googletest
# GIT_REPOSITORY https://github.com/google/googletest.git
# GIT_TAG        release-1.12.1
# )
# FetchContent_MakeAvailable(googletest)
# add_library(GTest::GTest INTERFACE IMPORTED)
# target_link_libraries(GTest::GTest INTERFACE gtest_main)

# CAVEAT: Use git submodule to integrate GTest, and make it available through
# add_subdirectory along with EXCLUDE_FROM_ALL to prevent installing GTest and
# GMock
add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

set(SOURCE_FILES src/queue/circ_array_queue_test.cpp)

add_executable(queue_tests ${SOURCE_FILES})

# target_include_directories(queue_tests PRIVATE ${QUEUE_HEADER_DIR})
# target_include_directories(queue_tests PRIVATE lib/googletest/googletest/include)
target_link_libraries(
    queue_tests PRIVATE
    queue
    GTest::gtest_main project_compiler_flags)

include(GoogleTest)
gtest_discover_tests(queue_tests)

# install(TARGETS queue_tests DESTINATION ${APP_INSTALL_BIN_DIR})