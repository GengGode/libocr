function(find_onnxruntime)

# 判断平台
if (WIN32)
    file(DOWNLOAD https://github.com/csukuangfj/onnxruntime-libs/releases/download/v1.16.3/onnxruntime-win-x64-static_lib-1.16.3.tar.bz2 ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib.tar.bz2)
elseif (UNIX)
    file(DOWNLOAD https://github.com/csukuangfj/onnxruntime-libs/releases/download/v1.16.3/onnxruntime-linux-x64-static_lib-1.16.3.zip ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib.zip)
endif ()

# 解压
if (WIN32)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib.tar.bz2 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/.cache)
elseif (UNIX)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib.zip WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/.cache)
endif ()

# 设置库路径
if (WIN32)
    set(ONNXRUNTIME_LIB_PATH ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib/lib/x64/Release)
elseif (UNIX)
    set(ONNXRUNTIME_LIB_PATH ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib/lib)
endif ()

# 设置头文件路径
set(ONNXRUNTIME_INCLUDE_PATH ${CMAKE_BINARY_DIR}/.cache/onnxruntime-static_lib/include/onnxruntime)

# 设置库
set(onnxruntime_LIBRARIES ${ONNXRUNTIME_LIB_PATH}/onnxruntime.lib)
set(onnxruntime_INCLUDE_DIRS ${ONNXRUNTIME_INCLUDE_PATH})

endfunction(find_onnxruntime)
