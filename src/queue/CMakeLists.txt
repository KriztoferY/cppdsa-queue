set(INCLUDE_FILES
    adt.hpp
    adt.inl
    circ_array_queue.hpp
    circ_array_queue.inl
)

set(SOURCE_FILES circ_array_queue.cpp)

add_library(queue SHARED STATIC ${INCLUDE_FILES} ${SOURCE_FILES})
set_property(TARGET queue PROPERTY VERSION "0.1.0")
set_property(TARGET queue PROPERTY SOVERSION "1")

# Make all subprojects not having to include the library
# using target_include_directories()
target_include_directories(queue
                           INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:${APP_INSTALL_INCLUDE_DIR}>
                           )

install(TARGETS queue DESTINATION ${APP_INSTALL_LIB_DIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${APP_INSTALL_INCLUDE_DIR})