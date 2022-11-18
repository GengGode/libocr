//
// Created by GengG on 2022/11/9.
//

#include "text_recognizer.h"
#include "../../resource/resource.h"

libocr::onnx::text_recognizer::text_recognizer()
{
    set_options();
    //===== this set model resource IDR ONNX MODEL =====
    auto model = libocr::utils::from_resource_load_onnx(IDR_ONNX_CHT);
    session = new Ort::Session(env, model.data, model.data_length, session_options);
    //===== this set keys resource IDR Txt  =====
    auto dict = libocr::utils::from_resource_load_txt(IDR_TXT_CHT_DICT);
    {
        auto dict_string = std::string((char*)dict.data, dict.data_length);
        std::istringstream in(dict_string);
        if (in) {
            std::string line;
            while (getline(in, line)) {
                // 剔除 /r
                line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                keys.push_back(line);
            }
        }
    }
    init_model();
}

libocr::onnx::text_recognizer::~text_recognizer()
{
    if (session != nullptr)
    {
        delete session;
        session = nullptr;
    }
}

void libocr::onnx::text_recognizer::set_options()
{
    //session_options.SetInterOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
}

void libocr::onnx::text_recognizer::init_model()
{
    // get input/output name
    get_input_name();
    get_output_name();
    // get input/output shape
    model_input_img_height = static_cast<int>(get_input_shape()[2]);
}

std::string libocr::onnx::text_recognizer::run(cv::Mat &input_image) {
    to_input_tensor(input_image);
    assert(input_tensor.IsTensor());
    Ort::RunOptions run_options = Ort::RunOptions{nullptr};
    session->Run(run_options, &input_name, &input_tensor, 1, &output_name, &output_tensor, 1);
    assert(output_tensors.size() == 1);
    assert(output_tensors.front().IsTensor());
    return from_output_tensor();
}

void libocr::onnx::text_recognizer::to_input_tensor(cv::Mat &src) {
    auto scale = model_input_img_height / (float) src.rows;
    
    // resize input img
    cv::Mat input_img;
    cv::resize(src, input_img, cv::Size(), scale, scale);
    // normalize input img : mat / 127.5 - 1.0
    cv::Mat input_img_norm;
    input_img.convertTo(input_img_norm, CV_32FC3, 1.0 / 127.5, -1.0);
    // set input shape
    std::array<int64_t, 4> input_shape = { 1,3,input_img.rows, input_img.cols };
    // size as input_shape : 1,3,48,192
    int input_size = 1 * 3 * input_img.rows * input_img.cols;
    // copy to vector<float>
    std::vector<float> input_data(input_size);
    // resort input_data
    int index = 0;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < input_img.rows; i++)
        {
            for (int j = 0; j < input_img.cols; j++)
            {
                input_data[index] = input_img_norm.at<cv::Vec3f>(i, j)[k];
                index++;
            }
        }
    }
    
    // memory input img
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    // create input tensor
    input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_size, input_shape.data(),
                                                   input_shape.size());
}

std::string libocr::onnx::text_recognizer::from_output_tensor() {
    auto               output_tensor_info = output_tensor.GetTensorTypeAndShapeInfo();
    auto               output_type        = output_tensor_info.GetElementType();
    auto               output_shape       = output_tensor_info.GetShape();
    auto               output_size        = output_tensor_info.GetElementCount();
    auto               output_data_ptr    = output_tensor.GetTensorMutableData<float>();
    std::vector<float> output_data(output_data_ptr, output_data_ptr + output_size);
    // re norm
    for (auto &v: output_data) {
        v = exp(v);
    }
    int output_shape_2 = static_cast<int>(output_shape[2]);
    // shape : 1, n, ?
    std::vector<std::vector<float>> output_data_2d;
    for (int i = 0; i < output_data.size(); i += output_shape_2)
    {
        std::vector<float> output_data_1d(output_data.begin() + i, output_data.begin() + i + output_shape_2);
        output_data_2d.push_back(output_data_1d);
    }
    // get max index, value
    std::vector<std::pair<int,float>> max_index_value;
    for (auto& v : output_data_2d)
    {
        auto max_index = static_cast<int>(std::max_element(v.begin(), v.end()) - v.begin());
        auto max_value = *std::max_element(v.begin(), v.end());
        max_index_value.push_back(std::make_pair(max_index, max_value));
    }
    
    auto &result = output_data_2d;
    std::string text_result = "";
    std::string last_word   = "";
    for (auto& v : result) {
        auto max_index = static_cast<int>(std::max_element(v.begin(), v.end()) - v.begin());
        //auto max_value = *std::max_element(v.begin(), v.end());
        auto word      = get_keys_char(max_index - 1);
        if (word != last_word && word != keys.back()) {
            text_result += word;
        }
        last_word      = word;
    }
    
    return text_result;
}
