//
// Created by GengG on 2022/11/9.
//

#include "ocr_manager.h"
#include "../onnx/text_detector/text_detector.h"
#include "../onnx/text_recognizer/text_recognizer.h"

libocr::ocr_manager::ocr_manager()
{
    text_det = new onnx::text_detector();
    text_rec = new onnx::text_recognizer();
}

libocr::ocr_manager &libocr::ocr_manager::get_instance()
{
    static ocr_manager instance;
    return instance;
}

libocr::ocr_manager::~ocr_manager()
{
    delete text_det;
    delete text_rec;
}

std::string libocr::ocr_manager::detect_and_recognize(const cv::Mat &image)
{
    std::string texts;
    for (auto &area : text_det->run(image))
        texts += recognize(image(area.rect));
    return texts;
}

std::string libocr::ocr_manager::recognize(const cv::Mat &image)
{
    return text_rec->run(image);
}

int libocr::ocr_manager::recognize(int image_width, int image_height, const char *image_data, int image_data_size,
                                   char *result, int result_size)
{
    cv::Mat image = cv::Mat(image_height, image_width, CV_8UC3, (void *)image_data);
    if (image.empty())
    {
        return -1;
    }
    if (image.channels() != 3)
    {
        return -2;
    }
    std::string text = recognize(image);
    if (text.size() > result_size)
    {
        return -1;
    }

    strcpy_s(result, result_size, text.c_str());
    return 0;
}

int libocr::ocr_manager::recognize(int image_width, int image_height, const char *image_data, unsigned int row_pitch,
                                   char *result, int result_size)
{
    cv::Mat image = cv::Mat(image_height, image_width, CV_8UC4, (void *)image_data, row_pitch);
    cv::Mat dst;
    cv::cvtColor(image, dst, cv::COLOR_RGBA2RGB);
    if (image.empty())
    {
        return -1;
    }
    std::string text = recognize(dst);
    if (text.size() > result_size)
    {
        return -1;
    }

    strcpy_s(result, result_size, text.c_str());
    return 0;
}

int libocr::ocr_manager::recognize(const char *image_data, int image_data_size, char *result, int result_size)
{
    auto image_array = cv::Mat(1, image_data_size, CV_8UC1, (void *)image_data);
    cv::Mat image = cv::imdecode(image_array, cv::IMREAD_COLOR);

    if (image.empty())
    {
        return -1;
    }
    if (image.channels() != 3)
    {
        return -2;
    }
    std::string text = recognize(image);
    if (text.size() > result_size)
    {
        return -1;
    }
    image.release();
    image_array.release();
    strcpy_s(result, result_size, text.c_str());
    return 0;
}

int libocr::ocr_manager::recognize(const char *image_file, char *result, int result_size)
{
    cv::Mat image = cv::imread(image_file, cv::IMREAD_COLOR);
    if (image.empty())
    {
        return -1;
    }
    if (image.channels() != 3)
    {
        return -2;
    }
    std::string text = recognize(image);
    if (text.size() > result_size)
    {
        return -1;
    }

    strcpy_s(result, result_size, text.c_str());
    return 0;
}
