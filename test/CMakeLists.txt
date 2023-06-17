cmake_minimum_required(VERSION 3.21)
project(libocr_test)

add_subdirectory(example_dynamiclink_loadtime)
add_subdirectory(example_dynamiclink_runtime)

add_test(NAME example_dynamiclink_loadtime COMMAND example_dynamiclink_loadtime)
add_test(NAME example_dynamiclink_runtime COMMAND example_dynamiclink_runtime)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
