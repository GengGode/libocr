CMAKE_MINIMUM_REQUIRED(VERSION 2.8) #设定最小版本号
PROJECT(libocr)                       #设定工程名

# 定义 LIBOCR_EXPORT
add_definitions(-DLIBOCR_EXPORT)

# 设置 动态库加载入口
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# 设置为C++17
set(CMAKE_CXX_STANDARD 17)

# Release模式
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    # 生成pdb文件
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

    # 设置 MT_StaticRelease
    message(STATUS "Release MT mode")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif ()
# Debug模式
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 生成pdb文件
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG /OPT:REF /OPT:ICF")

    # 设置 MTd_StaticDebug
    message(STATUS "Debug MTd mode")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:>")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MT")
endif ()

# 设置dll输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



# 设置 添加resource.rc资源
set(CMAKE_RC_COMPILER_INIT windres)
ENABLE_LANGUAGE(RC)

# 添加版本号文件和资源文件
if(MSVC)
    message(STATUS "Adding version resource")
    set(RESOURCE_RC "${CMAKE_SOURCE_DIR}/resource/resource_model.rc")
    # ${PROJECT_VERSION_MAJOR}, ${PROJECT_VERSION_MINOR}, ${PROJECT_VERSION_PATCH}
    set(PROJECT_VERSION_MAJOR 0)
    set(PROJECT_VERSION_MINOR 0)
    set(PROJECT_VERSION_PATCH 2)
    set(VERSIONINFO_RC "${CMAKE_BINARY_DIR}/resource.rc")
    configure_file("${CMAKE_SOURCE_DIR}/resource/resource.rc.in" "${VERSIONINFO_RC}")
endif()

#设定可执行二进制文件的目录
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#设定头文件目录
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src)

# 引入opencv 在3rdparty目录下
#INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/opencv/include)
#LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/opencv/x64/vc17/staticlib)

#set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/3rdparty/opencv/x64/vc17/staticlib)
# OpenCV_DIR
#find_package(OpenCV REQUIRED)

# 添加第三方库头文件目录 3rdparty/include
# INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include/opencv)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include/onnxruntime/core)

# 添加第三方库链接目录 3rdparty/lib
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/lib)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external)


add_library(libocr SHARED ${VERSIONINFO_RC} ${RESOURCE_RC}
        ${PROJECT_SOURCE_DIR}/include/libocr.h ${PROJECT_SOURCE_DIR}/src/libocr.cpp
        src/ocr/ocr.cpp
        src/ocr_manager/ocr_manager.cpp
        src/onnx/onnx.h
        src/onnx/text_recognizer/text_recognizer.cpp
        src/resource/resource.h
        src/utils/utils.h
        )


# 编译完成后，install到install目录
install(TARGETS libocr
        RUNTIME DESTINATION  ${PROJECT_SOURCE_DIR}/lib
        LIBRARY DESTINATION  ${PROJECT_SOURCE_DIR}/lib
        ARCHIVE DESTINATION  ${PROJECT_SOURCE_DIR}/lib
        )

# 添加测试项目 libocr_test
add_subdirectory(test)
# 拷贝生成的dll、lib到test目录
add_custom_command(TARGET libocr POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/libocr.lib
        ${CMAKE_BINARY_DIR}/test/libocr.lib
        )

add_custom_command(TARGET libocr POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/libocr.dll
        ${CMAKE_BINARY_DIR}/test/bin/libocr.dll
        )