//
// Created by GengG on 2022/11/9.
//
#ifdef USED_LIBOCOR_STATIC_LIB
#define _LIB
#endif
#ifndef _LIB
#ifdef LIBOCR_EXPORT
#define LIBOCR_API __declspec(dllexport)
#else
#define LIBOCR_API __declspec(dllimport)
#endif
#else
#define LIBOCR_API
#endif

// namespace : libocr
namespace libocr
{
    // typedef int LIBOCR_API error_code;
    // /// <summary>
    // /// 加载默认使用的模型
    // /// </summary>
    // /// <param name="model_path">模型路径</param>
    // /// <returns>错误码</returns>
    // LIBOCR_API error_code load_model(const char *model_path, const char *keys_path);
    //
    // LIBOCR_API error_code
    // load_model(const char *model_data, int model_data_size, const char *keys_data, int keys_data_size);
    //
    // LIBOCR_API error_code load_models(const char *model_tag, const char *model_path, const char *keys_path);
    //
    // LIBOCR_API error_code
    // load_models(const char *model_tag, const char *model_data, int model_data_size, const char *keys_data,
    //             int keys_data_size);
    //
    // LIBOCR_API error_code unload_model();
    //
    // LIBOCR_API error_code unload_models(const char *model_tag);
    //
    // LIBOCR_API error_code unload_all_models();
    // /// <summary>
    // /// 识别图片 传入图片data数据
    // /// </summary>
    // /// <param name="image_width">图片宽度</param>
    // /// <param name="image_height">图片高度</param>
    // /// <param name="image_data">图片数据</param>
    // /// <param name="image_data_size">图片数据大小</param>
    // /// <param name="result_buff">识别结果</param>
    // /// <param name="buff_size">识别结果大小</param>
    // /// <returns>错误码</returns>
    // LIBOCR_API error_code
    // recognize(int image_width, int image_height, const char *image_data, int image_data_size, char *result_buff,
    //           int buff_size);
    // /// <summary>
    // /// 识别图片 传入图片文件二进制数据
    // /// </summary>
    // /// <param name="image_data">图片数据</param>
    // /// <param name="image_data_size">图片数据大小</param>
    // /// <param name="result_buff">识别结果</param>
    // /// <param name="buff_size">识别结果大小</param>
    // /// <returns>错误码</returns>
    // LIBOCR_API error_code recognize(const char *image_data, int image_data_size, char *result_buff, int buff_size);

#ifdef  __cplusplus
    extern "C" {
#endif
    
    /// <summary>
    /// 加载默认使用的模型
    /// </summary>
    /// <param name="model_path">模型路径</param>
    /// <returns>错误码</returns>
    // LIBOCR_API error_code load_model_c(const char *model_path);
    // LIBOCR_API error_code load_models_c(const char *model_tag, const char *model_path);
    // LIBOCR_API error_code unload_models_c(const char *model_tag);
    // LIBOCR_API error_code unload_model_c();
    // LIBOCR_API error_code
    // recognize(const char *model_tag, int image_width, int image_height, const char *image_data, int image_data_size,
    //           char *result, int result_size);
    // LIBOCR_API error_code recognize_file(const char *model_tag, const char *image_file, char *result, int result_size);
    // LIBOCR_API error_code
    // recognize_file_data(const char *model_tag, const char *image_data, int image_data_size, char *result,
    //int result_size ) ;
    
    LIBOCR_API int ocr(const char *image_data, int image_data_size, char *result, int result_size);
    LIBOCR_API int
    ocr_image_data(int image_width, int image_height, const char *image_data, int image_data_size, char *result,
                   int result_size);
    LIBOCR_API int
    ocr_image_data_rgba(int image_width, int image_height, const char *image_data, unsigned int row_pitch,
                        char *result, int result_size);
    LIBOCR_API int ocr_file_data(const char *image_data, int image_data_size, char *result, int result_size);
    LIBOCR_API int ocr_file_path(const char *image_file, char *result, int result_size);
// allocate memory
    LIBOCR_API const char *ocr_file(const char *file_path, int *file_size);
    LIBOCR_API const char *ocr_image(int image_width, int image_height, const char *image_data, int image_data_size);
// free memory
    LIBOCR_API void free_char(char *p);

#ifdef  __cplusplus
    }
#endif
}