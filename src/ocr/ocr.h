//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_OCR_H
#define LIBOCR_OCR_H
#include "../onnx/text_recognizer/text_recognizer.h"
namespace libocr
{
    //class ocr
    //{
    //public:
    //    //int recognize_image_data(int image_width, int image_height, const char *image_data, int image_data_size, char *result, int result_size);
    //    //int recognize_file_data(const char *image_data, int image_data_size, char *result, int result_size);
    //    //int recognize_file(const char *image_file, char *result, int result_size);
    //};
    
    inline int recognize(int image_width, int image_height, const char *image_data, int image_data_size, char *result, int result_size);
    inline int recognize(const char *image_data, int image_data_size, char *result, int result_size);
    inline int recognize(const char *image_file, char *result, int result_size);
}

#endif //LIBOCR_OCR_H
