//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_ONNX_H
#define LIBOCR_ONNX_H

#include "../utils/include.h"
#include "../utils/utils.h"

namespace libocr::onnx
{
    class onnx
    {
    public:
        onnx(){};
        ~onnx(){};
        virtual void run(cv::Mat& input_image) = 0;
    public:
        Ort::Session* session = nullptr;
        Ort::Env env;
        Ort::SessionOptions session_options= Ort::SessionOptions();
    public:
        char* input_name;
        char* output_name;
    public:
        void get_input_name()
        {
            auto input_name_t = utils::get_input_name(session);
            input_name = new char[input_name_t.size() + 1];
            strcpy_s(input_name, input_name_t.size() + 1, input_name_t.c_str());
        }
        void get_output_name()
        {
            auto output_name_t = utils::get_output_name(session);
            output_name = new char[output_name_t.size() + 1];
            strcpy_s(output_name, output_name_t.size() + 1, output_name_t.c_str());
        }
        std::vector<int64_t> get_input_shape()
        {
            return utils::get_input_shape(session);
        }
    };
}

#endif //LIBOCR_ONNX_H
