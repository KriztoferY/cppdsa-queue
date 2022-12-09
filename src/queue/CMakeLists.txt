
cmake_minimum_required(VERSION 3.12)
project(cppdsa-queue LANGUAGES C CXX)

set(INCLUDE_FILES
    adt.hpp
    adt.inl
    circ_array_queue.hpp
    circ_array_queue.inl
)

set(SOURCE_FILES
    circ_array_queue.cpp
)

add_library(queue SHARED STATIC ${INCLUDE_FILES} ${SOURCE_FILES})

install(TARGETS queue DESTINATION ${APP_INSTALL_LIB_DIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${APP_INSTALL_INCLUDE_DIR})