//
// Created by GengG on 2022/11/9.
//
#include "libocr/libocr.h"
// #include "ocr/ocr.h"
#include "ocr_manager/ocr_manager.h"

int _stdcall ocr(const char *image_data, int image_data_size, char *result, int result_size)
{
    return ocr_file_data(image_data, image_data_size, result, result_size);
}

int _stdcall ocr_image_data(int image_width, int image_height, const char *image_data, int image_data_size, char *result,
                            int result_size)
{
    return libocr::recognize_image_data(image_width, image_height, image_data, image_data_size, result, result_size);
}

int _stdcall ocr_image_data_rgba(int image_width, int image_height, const char *image_data, unsigned int row_pitch,
                                 char *result, int result_size)
{
    return libocr::recognize_image_data(image_width, image_height, image_data, row_pitch, result, result_size);
}

int _stdcall ocr_file_data(const char *image_data, int image_data_size, char *result, int result_size)
{
    return libocr::recognize_file_data(image_data, image_data_size, result, result_size);
}

int _stdcall ocr_file_path(const char *image_file, char *result, int result_size)
{
    return libocr::recognize_file(image_file, result, result_size);
}

// allocate memory
const char *_stdcall ocr_file(const char *file_path, int file_size)
{
    char *buffer = new char[file_size];
    ocr_file_path(file_path, buffer, file_size);
    return buffer;
}

const char *_stdcall ocr_image(int image_width, int image_height, const char *image_data, int image_data_size)
{
    char *buffer = new char[1024];
    ocr_image_data(image_width, image_height, image_data, image_data_size, buffer, 1024);
    return buffer;
}

// free memory
void _stdcall free_char(char *p)
{
    // free(p);
    delete p;
}
