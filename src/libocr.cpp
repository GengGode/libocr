//
// Created by GengG on 2022/11/9.
//
#include "../include/libocr.h"
//#include "ocr/ocr.h"
#include "ocr_manager/ocr_manager.h"

int ocr_recognize_image_data(int image_width, int image_height, const char *image_data, int image_data_size, char *result, int result_size)
{
    return libocr::recognize_image_data(image_width, image_height, image_data, image_data_size, result, result_size);
}
int ocr_recognize_file_data(const char *image_data, int image_data_size, char *result, int result_size)
{
    return libocr::recognize_file_data(image_data, image_data_size, result, result_size);
}
int ocr_recognize_file(const char *image_file, char *result, int result_size)
{
    return libocr::recognize_file(image_file, result, result_size);
}

// free memory
void free_char(char *p)
{
    //free(p);
    delete p;
}
