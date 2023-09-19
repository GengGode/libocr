//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_OCR_MANAGER_H
#define LIBOCR_OCR_MANAGER_H

#include "utils/include.h"
namespace libocr
{
    namespace onnx {
        class text_recognizer;
    }
    
    class ocr_manager
    {
        onnx::text_recognizer* text_rec;
        ocr_manager();
    public:
        static ocr_manager& get_instance();
        ~ocr_manager();
    
        std::string recognize(cv::Mat& image);
        
        int recognize(int image_width, int image_height, const char *image_data, int image_data_size, char *result, int result_size);
        int recognize(int image_width, int image_height, const char *image_data, unsigned int row_pitch, char *result, int result_size);
        int recognize(const char *image_data, int image_data_size, char *result, int result_size);
        int recognize(const char *image_file, char *result, int result_size);
    };
    
    inline int recognize_image_data(int image_width, int image_height, const char *image_data, int image_data_size, char *result,
                                    int result_size){
        return libocr::ocr_manager::get_instance().recognize(image_width, image_height, image_data, image_data_size, result, result_size);
    };

    inline int recognize_image_data(int image_width, int image_height, const char *image_data, unsigned int row_pitch,
                                    char *result, int result_size) {
        return libocr::ocr_manager::get_instance().recognize(image_width, image_height, image_data, row_pitch, result, result_size);
    };
    
    inline int recognize_file_data(const char *image_data, int image_data_size, char *result, int result_size) {
        return libocr::ocr_manager::get_instance().recognize(image_data, image_data_size, result, result_size);
    };
    
    inline int recognize_file(const char *image_file, char *result, int result_size) {
        return libocr::ocr_manager::get_instance().recognize(image_file, result, result_size);
    };
}


#endif //LIBOCR_OCR_MANAGER_H
