cmake_minimum_required(VERSION 3.21)
project(libocr_test)

if(BUILD_SHARED_LIBS)
add_subdirectory(example_dynamiclink_loadtime)
add_subdirectory(example_dynamiclink_runtime)

add_test(NAME example_dynamiclink_loadtime COMMAND example_dynamiclink_loadtime)
add_test(NAME example_dynamiclink_runtime COMMAND example_dynamiclink_runtime)
else()
add_subdirectory(example_staticlink_compiletime)

add_test(NAME example_staticlink_compiletime COMMAND example_staticlink_compiletime)
endif()



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
