CMAKE_MINIMUM_REQUIRED(VERSION 2.8) #设定最小版本号
PROJECT(libocr)                       #设定工程名

set(CMAKE_BUILD_TYPE Release)

# 定义 LIBOCR_EXPORT
add_definitions(-DLIBOCR_EXPORT)

# 设置 动态库加载入口
set(CMAKE_SHARED_LIBRARY_PREFIX "")




# 设置为C++17
set(CMAKE_CXX_STANDARD 17)

# 设置编译选项

#设定可执行二进制文件的目录
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#设定存放编译出来的库文件的目录
# SET( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)

#并且把该目录设为连接目录
# LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib)

# find_package (opencv)
#设定头文件目录
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include)

# 添加第三方库头文件目录 3rdparty/include
# INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include/opencv)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/include/onnxruntime)

# 添加第三方库链接目录 3rdparty/lib
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/lib)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime)
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external)

# 添加静态库依赖
# opencv :
#   3rdparty/staticlib/opencv/ade.lib
#   3rdparty/staticlib/opencv/Ilmlmf.lib
#   3rdparty/staticlib/opencv/opencv_core452.lib
#   3rdparty/staticlib/opencv/ade.lib
#   3rdparty/staticlib/opencv/IlmImf.lib
#   3rdparty/staticlib/opencv/ippicvmt.lib
#   3rdparty/staticlib/opencv/ippiw.lib
#   3rdparty/staticlib/opencv/ittnotify.lib
#   3rdparty/staticlib/opencv/libjpeg-turbo.lib
#   3rdparty/staticlib/opencv/libopenjp2.lib
#   3rdparty/staticlib/opencv/libpng.lib
#   3rdparty/staticlib/opencv/libprotobuf.lib
#   3rdparty/staticlib/opencv/libtiff.lib
#   3rdparty/staticlib/opencv/libwebp.lib
#   3rdparty/staticlib/opencv/quirc.lib
#   3rdparty/staticlib/opencv/zlib.lib
#   3rdparty/staticlib/opencv/opencv_world460.lib
#   3rdparty/staticlib/opencv/opencv_img_hash460.lib
# onnxruntime :
#   3rdparty/staticlib/onnxruntime/onnxruntime_common.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_flatbuffers.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_framework.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_graph.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_mlas.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_optimizer.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_providers.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_session.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_test_utils.lib
#   3rdparty/staticlib/onnxruntime/onnxruntime_util.lib
# onnxruntime-external :
#   3rdparty/staticlib/onnxruntime-external/onnx_test_data_proto.lib
#   3rdparty/staticlib/onnxruntime-external/onnx.lib
#   3rdparty/staticlib/onnxruntime-external/onnx_proto.lib
#   3rdparty/staticlib/onnxruntime-external/libprotobuf-lite.lib
#   3rdparty/staticlib/onnxruntime-external/re2.lib
#   3rdparty/staticlib/onnxruntime-external/absl_base.lib
#   3rdparty/staticlib/onnxruntime-external/absl_throw_delegate.li
#   3rdparty/staticlib/onnxruntime-external/absl_raw_hash_set.lib
#   3rdparty/staticlib/onnxruntime-external/absl_hash.lib
#   3rdparty/staticlib/onnxruntime-external/absl_city.lib
#   3rdparty/staticlib/onnxruntime-external/absl_low_level_hash.lib
# 添加user32.lib gdi32.lib
# 添加libprotobuf.lib

SET( EXTRA_LIBS
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/ade.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/Ilmlmf.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/opencv_core452.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/ade.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/IlmImf.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/ippicvmt.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/ippiw.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/ittnotify.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/libjpeg-turbo.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/libopenjp2.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/libpng.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/libprotobuf.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/libtiff.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/libwebp.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/quirc.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/zlib.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/opencv_world460.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/opencv/opencv_img_hash460.lib

        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_common.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_flatbuffers.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_framework.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_graph.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_mlas.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_optimizer.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_providers.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_session.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_test_utils.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime/onnxruntime_util.lib

        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/onnx_test_data_proto.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/onnx.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/onnx_proto.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/libprotobuf-lite.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/re2.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/absl_base.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/absl_throw_delegate.li
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/absl_raw_hash_set.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/absl_hash.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/absl_city.lib
        ${PROJECT_SOURCE_DIR}/3rdparty/staticlib/onnxruntime-external/absl_low_level_hash.lib
    )

# 添加rc资源文件
SET(RESOURCES ${PROJECT_SOURCE_DIR}/resource/resource_model.rc)

# 添加src目录下所有cpp文件
AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/ libocr.cpp)
AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/ocr/ ocr.cpp)
AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/onnx/ onnx.cpp)
AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/onnx/text_recognizer/ text_recognizer.cpp)
AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/resource resource.h)
AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src/utils utils.h)


add_library(libocr SHARED ${PROJECT_SOURCE_DIR}/include/libocr.h ${PROJECT_SOURCE_DIR}/src/libocr.cpp)

# 添加cpp/h文件
#ADD_LIBRARY(libocr SHARED ${PROJECT_SOURCE_DIR}/include/libocr.h ${PROJECT_SOURCE_DIR}/src/libocr.cpp src/utils/include.h src/utils/utils.h src/resource/resource.h)

# target_link_libraries(libocr  ${EXTRA_LIBS} ${RESOURCES})

# target_link_libraries(libocr)
