set(resource_target_name ${BUILD_TARGET_NAME}_resource)
add_library(${resource_target_name} STATIC)
add_library(${BUILD_TARGET_NAME}::resource ALIAS ${resource_target_name})

target_compile_options(${resource_target_name} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
set_target_properties(${resource_target_name} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_options(${resource_target_name} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(list_of_resource_define)

# parse embed.list get all files
file(READ embed.list embed_list)
string(REPLACE "\n" ";" embed_list ${embed_list})
foreach(embed_file ${embed_list})
  message(STATUS "embed_file: ${embed_file}")
  set(file ${CMAKE_CURRENT_SOURCE_DIR}/${embed_file})
  # get file is exist
  if (EXISTS ${file})
    # get file content
    file(READ ${file} embed_file_content HEX)
    # get file size
    string(LENGTH ${embed_file_content} embed_file_size)
    ############################
    # size need / 2
    math(EXPR embed_file_size "${embed_file_size} / 2")
    ############################
    # get define name 
    string(REPLACE "." "_" embed_file_define ${embed_file})

    # add define Opt(name, size, define_name)
    set(list_of_resource_define "${list_of_resource_define} Opt(${embed_file}, ${embed_file_size}, ${embed_file_define})")
  endif()
endforeach()

message(STATUS "resource_define: ${list_of_resource_define}")
target_compile_definitions(${resource_target_name} PRIVATE list_of_resources=${list_of_resource_define})

target_sources(${resource_target_name}
  PUBLIC
    embed_resource.h
  PRIVATE
    embed_resource.cpp
)
target_include_directories(${resource_target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(embed_utils embed_utils/main.cpp)
target_compile_options(embed_utils PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_compile_options(embed_utils PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/MP>)
target_compile_definitions(embed_utils PRIVATE list_of_resources=${list_of_resource_define})

add_dependencies(${resource_target_name} embed_utils)

# 生成后事件
add_custom_command(
  TARGET ${resource_target_name}
  POST_BUILD
  # 将产出的lib文件中的resource:{xx}替换为实际的资源
  COMMAND $<TARGET_FILE:embed_utils> "$<TARGET_FILE:${resource_target_name}>" "${CMAKE_CURRENT_SOURCE_DIR}"
  VERBATIM  
)
