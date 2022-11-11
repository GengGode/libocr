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
        ~text_recognizer();
        void set_options();
        void init_model();
        void run(cv::Mat& input_image) override;
        
        std::string get_output();
    private:
        Ort::Value to_input_tensor(cv::Mat& src);
        void from_output_tensor(Ort::Value& output_tensor);
    private:
        std::string text_result;
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
    
    inline std::string ocr_run(text_recognizer& text_rec, cv::Mat& image)
    {
        text_rec.run(image);
        return text_rec.get_output();
    }
}
#endif //LIBOCR_TEXT_RECOGNIZER_H
