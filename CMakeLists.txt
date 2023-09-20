cmake_minimum_required(VERSION 3.21)
project(libocr)

# 定义 LIBOCR_EXPORT
add_definitions(-DLIBOCR_EXPORT)

# 设置 动态库加载入口
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# 设置为C++17
set(CMAKE_CXX_STANDARD 17)

# 设置UTF-8编码
add_definitions(-DUNICODE -D_UNICODE)
# msvc编译器设置utf-8编码
if (MSVC)
    add_compile_options("/utf-8")
endif ()

#=======================================================================================================================

# 设置编译目标
option(BUILD_TARGET "Build target" libocr)
set(BUILD_TARGET libocr)

## 设置编译类型
#option(BUILD_TYPE "Build type" "Release")
#
## 设置编译平台
#option(BUILD_PLATFORM "Build platform" "x64")

# 设置是否编译动态库
option(BUILD_SHARED_LIBS "Build shared libs" ON)
set(BUILD_SHARED_LIBS ON)

# 设置是否编译静态库
option(BUILD_STATIC_LIBS "Build static libs" OFF)
set(BUILD_STATIC_LIBS OFF)

# 设置是否编译测试
option(BUILD_TEST "Build test" ON)
set(BUILD_TEST ON)


if (BUILD_STATIC_LIBS AND BUILD_SHARED_LIBS)
    message(FATAL_ERROR "BUILD_STATIC_LIBS and BUILD_SHARED_LIBS can not be enabled at the same time")
endif ()
if (BUILD_STATIC_LIBS)
    # define _LIB
    add_definitions(-D_LIB)
endif ()

#=======================================================================================================================

# Release模式
    # 生成pdb文件
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

    # 设置 MT_StaticRelease
    message(STATUS "Configuring : MT_StaticRelease")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

# Debug模式
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 生成pdb文件
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG /OPT:REF /OPT:ICF")

    # 设置 MTd_StaticDebug
    message(STATUS "Configuring : MTd_StaticDebug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:>")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif ()

# 设置dll输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)


# 设置 添加resource.rc资源
set(CMAKE_RC_COMPILER_INIT windres)
ENABLE_LANGUAGE(RC)

# 添加版本号资源和模型资源
if (MSVC)
    # message(STATUS "Adding version resource")
    # ${PROJECT_VERSION_MAJOR}, ${PROJECT_VERSION_MINOR}, ${PROJECT_VERSION_PATCH}
    set(PROJECT_VERSION_MAJOR 0)
    set(PROJECT_VERSION_MINOR 1)
    set(PROJECT_VERSION_PATCH 1)
    set(VERSIONINFO_RC "${CMAKE_BINARY_DIR}/resource.rc")
    configure_file("${CMAKE_SOURCE_DIR}/resource/resource.rc.in" "${VERSIONINFO_RC}")
    message(STATUS "Version : ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

    # message(STATUS "Adding model resource")
    set(ONNX_MODEL_REC_FILE "${CMAKE_SOURCE_DIR}/resource/model_rec.onnx")
    set(ONNX_MODEL_DET_FILE "${CMAKE_SOURCE_DIR}/resource/model_det.onnx")
    if (EXISTS ${MODEL_ONNX_FILE})
        message(STATUS "Check Model : [yes]")
        #file(GLOB_RECURSE MODEL_FILES ${CMAKE_SOURCE_DIR}/model/*)
        #message(STATUS "Model files :" ${MODEL_FILES})
        #set(MODEL_RC "${CMAKE_BINARY_DIR}/model.rc")
        #configure_file("${CMAKE_SOURCE_DIR}/resource/model.rc.in" "${MODEL_RC}")
    else ()
        message(STATUS "Check Model : [no]")
        message(STATUS "rec model file : ${ONNX_MODEL_REC_FILE}")
        message(STATUS "det model file : ${ONNX_MODEL_DET_FILE}")
    endif ()
    set(RESOURCE_RC "${CMAKE_SOURCE_DIR}/resource/resource_model.rc")
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
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty/include/opencv)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty/include/onnxruntime/core)

# 添加第三方库链接目录 3rdparty/lib
LINK_DIRECTORIES(PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external)

# 编译动态库
if (BUILD_SHARED_LIBS)
    add_library(libocr SHARED ${VERSIONINFO_RC} ${RESOURCE_RC}
            include/libocr/libocr.h ${PROJECT_SOURCE_DIR}/src/libocr.cpp
            src/ocr/ocr.cpp
            src/ocr_manager/ocr_manager.cpp
            src/onnx/onnx.h
            src/onnx/text_detector/text_detector.h
            src/onnx/text_detector/text_detector.cpp
            src/onnx/text_recognizer/text_recognizer.h
            src/onnx/text_recognizer/text_recognizer.cpp
            src/resource/resource.h
            src/utils/utils.h
            )
endif ()
# 编译静态库
if (BUILD_STATIC_LIBS)
    add_library(libocr STATIC ${VERSIONINFO_RC} ${RESOURCE_RC}
            include/libocr/libocr.h ${PROJECT_SOURCE_DIR}/src/libocr.cpp
            src/ocr/ocr.cpp
            src/ocr_manager/ocr_manager.cpp
            src/onnx/onnx.h
            src/onnx/text_recognizer/text_recognizer.cpp
            src/resource/resource.h
            src/utils/utils.h
            )
endif ()

# 编译完成后，install到install目录
install(TARGETS libocr
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/lib
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib
        )


if (BUILD_TEST)
    # 添加测试项目 libocr_test
    enable_testing()
    add_subdirectory(test)
    # 拷贝生成的dll、lib到test目录

    # 如果使用Visual Studio系列编译器 拷贝目录则在bin/Debug或bin/Release下
    if (MSVC)
        # 如果使用MinGW系列编译器 拷贝目录则在bin下
        add_custom_command(TARGET libocr POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_LIST_DIR}/lib/libocr.lib
                ${CMAKE_BINARY_DIR}/test/libocr.lib
                )
        if (BUILD_SHARED_LIBS)
            add_custom_command(TARGET libocr POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_LIST_DIR}/bin/libocr.dll
                    ${CMAKE_BINARY_DIR}/test/bin/libocr.dll
                    )
        endif ()
    else()
        # 如果使用MinGW系列编译器 拷贝目录则在bin下
        add_custom_command(TARGET libocr POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_LIST_DIR}/bin/libocr.lib
                ${CMAKE_BINARY_DIR}/test/libocr.lib
                )
        if (BUILD_SHARED_LIBS)
            add_custom_command(TARGET libocr POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_LIST_DIR}/bin/libocr.dll
                    ${CMAKE_BINARY_DIR}/test/bin/libocr.dll
                    )
        endif ()
    endif ()
endif ()


#=======================================================================================================================
message(STATUS "===============================")
message(STATUS "BUILD_TARGET : ${BUILD_TARGET}")
message(STATUS "BUILD_SHARED_LIBS : ${BUILD_SHARED_LIBS}")
message(STATUS "BUILD_STATIC_LIBS : ${BUILD_STATIC_LIBS}")
message(STATUS "BUILD_TEST : ${BUILD_TEST}")