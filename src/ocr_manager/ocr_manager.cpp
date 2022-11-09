//
// Created by GengG on 2022/11/9.
//

#include "ocr_manager.h"

libocr::ocr_manager::ocr_manager() {

}

libocr::ocr_manager &libocr::ocr_manager::get_instance() {
    static ocr_manager instance;
    return instance;
}

std::string libocr::ocr_manager::recognize(cv::Mat &image) {
    return text_recognizer::ocr_run(text_recognizer_, image);
    return std::string();
}

int libocr::ocr_manager::recognize(int image_width, int image_height, const char *image_data, int image_data_size,
                                              char *result, int result_size) {
    return 0;
}

int libocr::ocr_manager::recognize(const char *image_data, int image_data_size, char *result, int result_size) {
    return 0;
}

int libocr::ocr_manager::recognize(const char *image_file, char *result, int result_size) {
    return 0;
}
