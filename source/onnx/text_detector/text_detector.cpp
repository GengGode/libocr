//
// Created by GengG on 2023/09/20.
//

#include "text_detector.h"
#include "../../resource/resource.h"

libocr::onnx::text_detector::text_detector()
{
    set_options();
    //===== this set model resource IDR ONNX MODEL =====
    auto model = onnx::from_resource_load_onnx(IDR_ONNX_DET);
    session = std::make_shared<Ort::Session>(env, model.data, model.data_length, session_options);

    init_model();
}

void libocr::onnx::text_detector::set_options()
{
    // session_options.SetInterOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
}

void libocr::onnx::text_detector::init_model()
{
    // get input/output name
    get_input_name();
    get_output_name();
    // get input/output shape
    model_input_img_max_size = 1024;
}

std::vector<libocr::onnx::text_detector::text_area> libocr::onnx::text_detector::run(const cv::Mat& input_image)
{
    // note(zyxeeker): 需要重置输出节点防止输入不同大小输时出错
    if (output_tensor != nullptr)
    {
        output_tensor = Ort::Value{ nullptr };
    }
    to_input_tensor(input_image);
    Ort::RunOptions run_options = Ort::RunOptions{ nullptr };
    session->Run(run_options, &input_name, &input_tensor, 1, &output_name, &output_tensor, 1);
    return from_output_tensor();
}

void libocr::onnx::text_detector::to_input_tensor(const cv::Mat& src)
{
    const static auto align_to_32 = [](int value) -> double { return value < 32 ? 32 : ((value + 31) / 32 - 1) * 32; };
    scale_size_width = 1.0 * align_to_32(src.cols) / (double)src.cols;
    scale_size_height = 1.0 * align_to_32(src.rows) / (double)src.rows;
    // resize input img
    cv::Mat input_img;
    cv::resize(src, input_img, cv::Size(), scale_size_width, scale_size_height);
#ifndef normalize
    // set input shape
    std::array<int64_t, 4> input_shape = { 1, 3, input_img.rows, input_img.cols };
    // size as step
    int input_step = input_img.rows * input_img.cols;
    // size as input_shape : 1,3,48,192
    int input_size = 1 * 3 * input_step;
    // copy to vector<float>
    std::vector<float> input_data(input_size);
    // resort input_data
    std::vector<float> norms = { 1.0 / 0.229 / 255.0, 1.0 / 0.224 / 255.0, 1.0 / 0.225 / 255.0 };
    std::vector<float> means = { 0.485 * 255, 0.456 * 255, 0.406 * 255 };
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < input_img.rows; i++)
        {
            for (int j = 0; j < input_img.cols; j++)
            {
                float value = input_img.data[i * input_img.cols * 3 + j * 3 + k] * norms[k] - means[k] * norms[k];
                input_data[k * input_step + i * input_img.cols + j] = value;
            }
        }
    }
#else
    // normalize input img : mat / [0.229, 0.224, 0.225] - [0.485, 0.456, 0.406]
    cv::Mat input_img_norm;
    input_img.convertTo(input_img_norm, CV_32FC3, 1.0 / 0.226 / 255.0, -1.0 / 0.226 * 0.449);
    // set input shape
    std::array<int64_t, 4> input_shape = { 1, 3, input_img.rows, input_img.cols };
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
#endif

    // memory input img
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    // create input tensor
    input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_size, input_shape.data(), input_shape.size());
}

}

std::vector<libocr::onnx::text_detector::text_area> libocr::onnx::text_detector::from_output_tensor()
{
    auto output_tensor_info = output_tensor.GetTensorTypeAndShapeInfo();
    auto output_type = output_tensor_info.GetElementType();
    auto output_shape = output_tensor_info.GetShape();
    auto output_size = output_tensor_info.GetElementCount();
    auto output_data_ptr = output_tensor.GetTensorMutableData<float>();
    std::vector<float> output_data(output_data_ptr, output_data_ptr + output_size);
    // out size
    int output_shape_height = static_cast<int>(output_shape[2]);
    int output_shape_width = static_cast<int>(output_shape[3]);
    size_t output_shape_size = output_shape_height * output_shape_width;
    // out data
    cv::Mat output_img(output_shape_height, output_shape_width, CV_32FC1, output_data.data());
    cv::Mat output_img_norm;
    // out image to uint8
    cv::normalize(output_img, output_img_norm, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::Mat output_img_bin = output_img_norm > 75;
    // find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(output_img_bin, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    std::vector<text_area> text_areas;
    for (auto& contour : contours)
    {
        cv::Rect rect = cv::boundingRect(contour);
        cv::RotatedRect min_rect = cv::minAreaRect(contour);
        // filter small area
        if (min_rect.size.width < 4 || min_rect.size.height < 4)
        {
            continue;
        }
        std::vector<cv::Point2f> points;
        min_rect.points(points);
        auto score = min_rect.size.area() / cv::contourArea(contour);
        // filter score less than 0.5
        if (score < 0.5)
        {
            continue;
        }
        text_area area;
        area.score = score;
        area.rect = cv::Rect(rect.x / scale_size_width, rect.y / scale_size_height, rect.width / scale_size_width, rect.height / scale_size_height);
        for (auto& point : points)
        {
            area.points.push_back(cv::Point(static_cast<int>(point.x / scale_size_width), static_cast<int>(point.y / scale_size_height)));
        }

        text_areas.push_back(area);
    }

    return text_areas;
}
