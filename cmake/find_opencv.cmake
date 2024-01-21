function(find_opencv opencv_dir_vaule)
    set(base_dir ${CMAKE_BINARY_DIR}/.cache)
    set(download_dir ${base_dir}/opencv-download)
    set(extract_dir ${base_dir}/opencv-extract)
    set(install_dir ${base_dir}/opencv-static_lib)
    set(download_file ${download_dir}/LICENSE)
    set(extract_file ${extract_dir})


    # include(FetchContent)
    # FetchContent_Declare(opencv GIT_REPOSITORY https://github.com/opencv/opencv.git GIT_TAG 4.8.0 GIT_SHALLOW 1)

    # 手动clone到下载目录
    if(NOT EXISTS ${download_file})
        message(STATUS "download opencv")
        execute_process(COMMAND git clone --depth 1 https://github.com/opencv/opencv.git ${download_dir})
    endif()
    # get opencv version
    execute_process(COMMAND git describe --tags  WORKING_DIRECTORY ${download_dir} OUTPUT_VARIABLE opencv_version)
    # split . to get major.minor.patch
    string(REPLACE "." "" opencv_version_str ${opencv_version})
    string(SUBSTRING ${opencv_version_str} 0 3 opencv_version_str)

    # set(BUILD_SHARED_LIBS OFF)
    # set(OPENCV_CONFIG_FILE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/.deps/opencv_gen_include)
    # # disable modules
    # set(BUILD_opencv_apps OFF)
    # set(BUILD_opencv_aruco OFF)
    # set(BUILD_opencv_bgsegm OFF)
    # set(BUILD_opencv_bioinspired OFF)
    # set(BUILD_opencv_calib3d OFF)
    # set(BUILD_opencv_ccalib OFF)
    # set(BUILD_opencv_core ON)
    # set(BUILD_opencv_datasets OFF)
    # set(BUILD_opencv_dnn OFF)
    # set(BUILD_opencv_dnn_objdetect OFF)
    # set(BUILD_opencv_dnn_superres OFF)
    # set(BUILD_opencv_dpm OFF)
    # set(BUILD_opencv_face OFF)
    # set(BUILD_opencv_flann OFF)
    # set(BUILD_opencv_features2d OFF)
    # set(BUILD_opencv_fuzzy OFF)
    # set(BUILD_opencv_gapi OFF)
    # set(BUILD_opencv_hfs OFF)
    # set(BUILD_opencv_highgui OFF)
    # set(BUILD_opencv_imgcodecs ON)
    # set(BUILD_opencv_imgproc ON)
    # set(BUILD_opencv_intensity_transform OFF)
    # set(BUILD_opencv_line_descriptor OFF)
    # set(BUILD_opencv_mcc OFF)
    # set(BUILD_opencv_ml OFF)
    # set(BUILD_opencv_objdetect OFF)
    # set(BUILD_opencv_optflow OFF)
    # set(BUILD_opencv_phase_unwrapping OFF)
    # set(BUILD_opencv_photo OFF)
    # set(BUILD_opencv_plot OFF)
    # set(BUILD_opencv_quality OFF)
    # set(BUILD_opencv_rapid OFF)
    # set(BUILD_opencv_reg OFF)
    # set(BUILD_opencv_rgbd OFF)
    # set(BUILD_opencv_saliency OFF)
    # set(BUILD_opencv_shape OFF)
    # set(BUILD_opencv_stereo OFF)
    # set(BUILD_opencv_stitching OFF)
    # set(BUILD_opencv_structured_light OFF)
    # set(BUILD_opencv_superres OFF)
    # set(BUILD_opencv_surface_matching OFF)
    # set(BUILD_opencv_text OFF)
    # set(BUILD_opencv_tracking OFF)
    # set(BUILD_opencv_ts OFF)
    # set(BUILD_opencv_video OFF)
    # set(BUILD_opencv_videoio OFF)
    # set(BUILD_opencv_videostab OFF)
    # set(BUILD_opencv_world ON)
    # set(BUILD_opencv_wechat_qrcode OFF)
    # set(BUILD_opencv_xfeatures2d OFF)
    # set(BUILD_opencv_ximgproc OFF)
    # set(BUILD_opencv_xobjdetect OFF)
    # set(BUILD_opencv_xphoto OFF)
    # # disable python
    # set(BUILD_opencv_python_bindings_generator OFF)
    # set(BUILD_opencv_python_tests OFF)
    # # disable java
    # set(BUILD_JAVA OFF)
    # set(BUILD_opencv_java_bindings_generator OFF)
    # # disable js
    # set(BUILD_opencv_js OFF)
    # set(BUILD_opencv_js_bindings_generator OFF)
    # # disable objc
    # set(BUILD_opencv_objc_bindings_generator OFF)
    # # not test
    # set(BUILD_TESTS OFF)
    # set(BUILD_PERF_TESTS OFF)
    # set(BUILD_EXAMPLES OFF)
    # set(BUILD_DOCS OFF)
    # set(BUILD_WITH_DEBUG_INFO OFF)
    # # no itt
    # set(WITH_ITT OFF)
    # set(BUILD_ITT OFF)
    # set(ccitt OFF)
    # # pic
    # set(BUILD_SHARED_LIBS OFF)
    # set(BUILD_WITH_STATIC_CRT ON)
    # # 启用位置无关代码
    # set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    # # 设置安装位置
    # set(CMAKE_INSTALL_PREFIX ${install_dir})
    # FetchContent_MakeAvailable(opencv)
    # 手动cmake build到解压目录
    if((NOT EXISTS ${install_dir}/lib/opencv_core${opencv_version_str}.lib AND NOT EXISTS ${install_dir}/lib/opencv_world${opencv_version_str}.lib ) AND NOT EXISTS ${install_dir}/x64/vc17/staticlib/OpenCVConfig.cmake)
        file(MAKE_DIRECTORY ${extract_file})
        set(opencv_build_dir ${extract_file}/build)
        file(MAKE_DIRECTORY ${opencv_build_dir})
        if (WIN32)
            set(CMAKE_MAKE_PROGRAM "Visual Studio 17 2022")
            else()
            set(CMAKE_MAKE_PROGRAM "make")
        endif()
        message(STATUS "build opencv static library CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}")
        execute_process(COMMAND cmake -G "${CMAKE_MAKE_PROGRAM}" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${install_dir} -DBUILD_SHARED_LIBS=OFF
        -DBUILD_opencv_apps=OFF 
        -DBUILD_opencv_calib3d=OFF 
        -DBUILD_opencv_dnn=OFF 
        -DBUILD_opencv_features2d=OFF 
        -DBUILD_opencv_flann=OFF 
        -DBUILD_opencv_gapi=OFF 
        -DBUILD_opencv_highgui=OFF 
        -DBUILD_opencv_ml=OFF 
        -DBUILD_opencv_photo=OFF 
        -DBUILD_opencv_video=OFF 
        -DBUILD_opencv_videoio=OFF 
        -DBUILD_opencv_java_bindings_generator=OFF
        -DBUILD_opencv_js_bindings_generator=OFF
        -DBUILD_opencv_objc_bindings_generator=OFF
        -DBUILD_opencv_python_bindings_generator=OFF
        -DBUILD_opencv_python_tests=OFF
        -DBUILD_opencv_core=ON
        -DBUILD_opencv_imgcodecs=ON 
        -DBUILD_opencv_imgproc=ON 
        -DBUILD_opencv_world=OFF 
        -DBUILD_TESTS=OFF 
        -DBUILD_PERF_TESTS=OFF
        -DBUILD_EXAMPLES=OFF 
        -DBUILD_DOCS=OFF 
        -DBUILD_WITH_DEBUG_INFO=OFF 
        -DWITH_ITT=OFF -DBUILD_ITT=OFF -Dccitt=OFF 
        -DWITH_VTK=OFF -DWITH_WIN32UI=OFF -DWITH_OPENCL=OFF -DWITH_ONNX=OFF
        -DWITH_IPP=OFF 
        -DWITH_IPP_IW=OFF 
        -DCV_TRACE=OFF
        -DWITH_FFMEPG=OFF -DWITH_GSTREAMER=OFF -DWITH_DIRECTX=OFF -DWITH_MSMF=OFF -DWITH_1394=OFF -DWITH_DSHOW=OFF

        -DBUILD_SHARED_LIBS=OFF 
        -DBUILD_WITH_STATIC_CRT=ON 
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON 
        ${download_dir} WORKING_DIRECTORY ${opencv_build_dir})
        execute_process(COMMAND cmake --build . --config Release WORKING_DIRECTORY ${opencv_build_dir})
        execute_process(COMMAND cmake --build . --target install --config Release WORKING_DIRECTORY ${opencv_build_dir})
        
        if(NOT EXISTS ${install_dir}/x64/vc17/staticlib/OpenCVConfig.cmake)
            message(FATAL_ERROR "opencv build failed")
        endif()
    endif()

    # # 安装opencv
    # install(DIRECTORY ${install_dir}/ DESTINATION ${CMAKE_INSTALL_PREFIX} USE_SOURCE_PERMISSIONS)

    if(EXISTS ${install_dir}/x64/vc17/staticlib/OpenCVConfig.cmake)
        # rm *.cmake
        file(GLOB cmake_files ${install_dir}/x64/vc17/staticlib/*.cmake)
        foreach(cmake_file ${cmake_files})
            file(REMOVE ${cmake_file})
        endforeach()

        # copy x64/vc17/staticlib to install_dir/lib
        file(GLOB lib_files ${install_dir}/x64/vc17/staticlib/*.lib)
        foreach(lib_file ${lib_files})
            file(COPY ${lib_file} DESTINATION ${install_dir}/lib)
        endforeach()

        # rm x64/vc17/staticlib
        file(REMOVE_RECURSE ${install_dir}/x64)
        file(REMOVE_RECURSE ${install_dir}/etc)

    endif()

    set(${opencv_dir_vaule} ${install_dir} PARENT_SCOPE)
    message(STATUS "auto find opencv done")
endfunction()
