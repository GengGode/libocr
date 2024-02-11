//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_TEXT_RECOGNIZER_H
#define LIBOCR_TEXT_RECOGNIZER_H
#include "../onnx.h"

namespace libocr::onnx
{
    class text_recognizer : protected onnx
    {
    public:
        text_recognizer();

        ~text_recognizer() = default;

        void set_options();

        void init_model();

        std::string run(const cv::Mat& input_image);

    private:
        Ort::Value input_tensor{ nullptr };
        Ort::Value output_tensor{ nullptr };

        void to_input_tensor(const cv::Mat& src);

        std::string from_output_tensor();

    private:
        std::vector<std::string> keys;
        int model_input_img_height = 48;

        std::string get_keys_char(int index)
        {
            if (index < 0 || index >= keys.size())
            {
                return keys.back();
            }
            return keys[index];
        }
    };

    inline static std::string ocr_run(text_recognizer& text_rec, cv::Mat& image)
    {
        return text_rec.run(image);
    }
} // namespace libocr::onnx
#endif // LIBOCR_TEXT_RECOGNIZER_H
