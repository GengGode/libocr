CMAKE_MINIMUM_REQUIRED(VERSION 2.8) #设定最小版本号
PROJECT(libocr)                       #设定工程名

# 定义 LIBOCR_EXPORT
add_definitions(-DLIBOCR_EXPORT)

# 设置 动态库加载入口
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# 设置为C++17
set(CMAKE_CXX_STANDARD 17)

# 生成pdb文件
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

message(STATUS "Release mode")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:>")

# 设置 MT_StaticRelease
if (WIN32)
    message(STATUS "Release MT mode")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

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

# 添加第三方库头文件目录 3rdparty/include
# INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include/opencv)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include/onnxruntime/core)

# 添加第三方库链接目录 3rdparty/lib
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/lib)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external)

## 添加src目录下所有cpp文件
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/ libocr.cpp)
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/ocr/ ocr.cpp)
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/ocr_manager/ ocr_manager)
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/onnx/ onnx)
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/onnx/text_recognizer/ text_recognizer)
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/resource resource.h)
#AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/utils utils.h)


add_library(libocr SHARED ${VERSIONINFO_RC} ${RESOURCE_RC}
        ${PROJECT_SOURCE_DIR}/include/libocr.h ${PROJECT_SOURCE_DIR}/src/libocr.cpp
        src/ocr/ocr.cpp
        src/ocr_manager/ocr_manager.cpp
        src/onnx/onnx.h
        src/onnx/text_recognizer/text_recognizer.cpp
        src/resource/resource.h
        src/utils/utils.h
        )
