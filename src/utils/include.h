//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_INCLUDE_H
#define LIBOCR_INCLUDE_H

// opencv
#include <opencv2/opencv.hpp>
// onnxruntime
#include <session/onnxruntime_cxx_api.h>
//#include <onnxruntime/core/session/onnxruntime_cxx_api.h>
// windows
#ifdef _WIN32
#include <windows.h>
#endif

//"kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"

#pragma comment(lib, "onnxruntime_common.lib")
#pragma comment(lib, "onnxruntime_flatbuffers.lib")
#pragma comment(lib, "onnxruntime_framework.lib")
#pragma comment(lib, "onnxruntime_graph.lib")
#pragma comment(lib, "onnxruntime_mlas.lib")
#pragma comment(lib, "onnxruntime_mocked_allocator.lib")
#pragma comment(lib, "onnxruntime_optimizer.lib")
#pragma comment(lib, "onnxruntime_providers.lib")
#pragma comment(lib, "onnxruntime_session.lib")
#pragma comment(lib, "onnxruntime_test_utils.lib")
#pragma comment(lib, "onnxruntime_util.lib")

#pragma comment(lib, "onnx_test_data_proto.lib")
#pragma comment(lib, "onnx_test_runner_common.lib")
#pragma comment(lib, "onnx.lib")
#pragma comment(lib, "onnx_proto.lib")
#pragma comment(lib, "libprotobuf-lite.lib")
#pragma comment(lib, "re2.lib")
#pragma comment(lib, "absl_base.lib")
#pragma comment(lib, "absl_throw_delegate.lib")
#pragma comment(lib, "absl_raw_hash_set.lib")
#pragma comment(lib, "absl_hash.lib")
#pragma comment(lib, "absl_city.lib")
#pragma comment(lib, "absl_low_level_hash.lib")

#pragma comment(lib, "ade.lib")
#pragma comment(lib, "IlmImf.lib")
#pragma comment(lib, "ippicvmt.lib")
#pragma comment(lib, "ippiw.lib")
#pragma comment(lib, "ittnotify.lib")
#pragma comment(lib, "libjpeg-turbo.lib")
#pragma comment(lib, "libopenjp2.lib")
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libtiff.lib")
#pragma comment(lib, "libwebp.lib")
#pragma comment(lib, "quirc.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "opencv_world460.lib")
#pragma comment(lib, "opencv_img_hash460.lib")

#endif //LIBOCR_INCLUDE_H
