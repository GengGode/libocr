cmake_minimum_required(VERSION 3.21)
project(libocr_test)

# 设置为C++17
set(CMAKE_CXX_STANDARD 17)

# 生成pdb文件
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

# 设置 MT_StaticRelease
message(STATUS "Release MT mode")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

# 设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置源文件目录
aux_source_directory(. SRC_LIST)

# 设置依赖库目录
link_directories(${CMAKE_BINARY_DIR}/bin)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 设置依赖库
set(LIBS libocr.lib)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 链接依赖库
target_link_libraries(${PROJECT_NAME} ${LIBS})

# 设置工作目录
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message(STATUS "VS_DEBUGGER_WORKING_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# 设置启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# 拷贝测试图片到输出目录
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/image/test.png DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
