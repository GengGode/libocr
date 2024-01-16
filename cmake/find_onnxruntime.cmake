function(find_onnxruntime onnxruntime_dir_value)
    set(base_dir ${CMAKE_BINARY_DIR}/.cache)
    set(download_dir ${base_dir}/onnxruntime-download)
    set(extract_dir ${base_dir}/onnxruntime-extract)
    set(install_dir ${base_dir}/onnxruntime-static_lib)
    set(download_file ${download_dir}/onnxruntime.zip)
    set(extract_file ${extract_dir})

    # 平台判断
    if (WIN32)
        set(download_url https://github.com/csukuangfj/onnxruntime-libs/releases/download/v1.16.3/onnxruntime-win-x64-static_lib-1.16.3.tar.bz2)
    elseif (UNIX)
        set(download_url https://github.com/csukuangfj/onnxruntime-libs/releases/download/v1.16.3/onnxruntime-linux-x64-static_lib-1.16.3.zip)
    endif ()

    # 下载
    if(NOT EXISTS ${download_file})
        message(STATUS "Downloading onnxruntime from ${download_url} to ${download_file}")
        file(DOWNLOAD ${download_url} ${download_file} SHOW_PROGRESS)
        set(file_size 0)
        file(READ ${download_file} file_content HEX)
        string(LENGTH "${file_content}" file_size)
        message(STATUS "Downloaded onnxruntime ${file_size} bytes")
        if (file_size EQUAL 0)
            message(FATAL_ERROR "Downloaded onnxruntime ${file_size} bytes, but expected 0 bytes")
        endif ()
    endif()

    # 解压
    if(NOT EXISTS ${extract_file})
        file(MAKE_DIRECTORY ${extract_file})
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${download_file} WORKING_DIRECTORY ${extract_file})

        if (NOT EXISTS ${extract_file})
            message(FATAL_ERROR "Extracted onnxruntime ${extract_file} does not exist")
        endif()
    endif()

    # 安装
    if(NOT EXISTS ${install_dir})
        file(MAKE_DIRECTORY ${install_dir})
        file(GLOB onnxruntime_dir_path ${extract_file}/onnxruntime*)
        get_filename_component(onnxruntime_dir_name ${onnxruntime_dir_path} NAME)
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${extract_file}/${onnxruntime_dir_name} ${install_dir})

        if (NOT EXISTS ${install_dir})
            message(FATAL_ERROR "Installed onnxruntime ${install_dir} does not exist")
        endif()
    endif()

    # 设置变量
    set(${onnxruntime_dir_value} ${install_dir} PARENT_SCOPE)
    message(STATUS "auto find onnxruntime done")
endfunction(find_onnxruntime)
