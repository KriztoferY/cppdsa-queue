add_subdirectory(queue)

add_executable(queue_demo demo.cpp)
add_executable(queue_merge_demo demo_merge.cpp)

set_target_properties(queue_demo PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(queue_merge_demo PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(queue_demo PUBLIC
  "${PROJECT_BINARY_DIR}" # ProjectConfig.h
)

target_link_libraries(queue_demo PUBLIC queue project_compiler_flags)
target_link_libraries(queue_merge_demo PUBLIC queue project_compiler_flags)

install(TARGETS queue_demo DESTINATION ${APP_INSTALL_BIN_DIR})
install(TARGETS queue_merge_demo DESTINATION ${APP_INSTALL_BIN_DIR})
install(
  FILES "${PROJECT_BINARY_DIR}/ProjectConfig.h"
  DESTINATION ${APP_INSTALL_INCLUDE_DIR}
)