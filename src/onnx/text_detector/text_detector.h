//
// Created by GengG on 2023/09/20.
//

#ifndef LIBOCR_TEXT_DETECTOR_H
#define LIBOCR_TEXT_DETECTOR_H
#include "../onnx.h"

namespace libocr::onnx
{
    class text_detector : protected onnx
    {
    public:
        text_detector();

        ~text_detector() = default;

        void set_options();

        void init_model();

        struct text_area
        {
            std::vector<cv::Point> points;
            cv::Rect rect;
            double score;
        };
        std::vector<text_area> run(cv::Mat &input_image);

    private:
        Ort::Value input_tensor{nullptr};
        Ort::Value output_tensor{nullptr};
        void to_input_tensor(cv::Mat &src);

        std::vector<text_area> from_output_tensor();

    private:
        int model_input_img_max_size;
        double scale_size_width;
        double scale_size_height;
    };
}
#endif // LIBOCR_TEXT_DETECTOR_H
