//
// Created by GengG on 2022/11/9.
//

#if defined(_WIN32) || defined(_WIN64)
    #ifdef LIBOCR_EXPORTS
        #define LIBOCR_API __declspec(dllexport)
    #else
        #define LIBOCR_API __declspec(dllimport)
    #endif
#else
    #define LIBOCR_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif
#if NewAPI
    struct ocr_text;
    typedef struct ocr_text ocr_text_t;
    typedef ocr_text_t* ocr_text_ptr;

    LIBOCR_API ocr_text_ptr text_create();
    LIBOCR_API void text_get_content(ocr_text_ptr text, char* buff, int buff_size);
    LIBOCR_API void text_destroy(ocr_text_ptr text);

    struct ocr_image;
    typedef struct ocr_image ocr_image_t;
    typedef ocr_image_t* ocr_image_ptr;

    LIBOCR_API ocr_image_ptr image_create();
    LIBOCR_API void image_set_data(ocr_image_ptr image, int width, int height, const char* image_data, int image_data_size);
    LIBOCR_API void image_set_data_rgba(ocr_image_ptr image, int width, int height, const char* image_data, unsigned int row_pitch);
    LIBOCR_API void image_set_file(ocr_image_ptr image, const char* image_file);
    LIBOCR_API void image_set_file_data(ocr_image_ptr image, const char* image_data, int image_data_size);
    LIBOCR_API void image_destroy(ocr_image_ptr image);

    struct ocr_result;
    typedef struct ocr_result ocr_result_t;
    typedef ocr_result_t* ocr_result_ptr;

    LIBOCR_API ocr_result_ptr result_create();
    LIBOCR_API int result_get_text_count(ocr_result_ptr result);
    LIBOCR_API void result_get_text(ocr_result_ptr result, int index, ocr_text_ptr text);
    LIBOCR_API void result_get_text_content(ocr_result_ptr result, int index, char* buff, int buff_size);
    LIBOCR_API void result_destroy(ocr_result_ptr result);

    struct ocr_engine_config;
    typedef struct ocr_engine_config ocr_engine_config_t;
    typedef ocr_engine_config_t* ocr_engine_config_ptr;

    LIBOCR_API ocr_engine_config_ptr engine_config_create();
    LIBOCR_API void config_set_parameter(ocr_engine_config_ptr config, const char* key, const char* value);
    LIBOCR_API void config_set_parameter_int(ocr_engine_config_ptr config, const char* key, int value);
    LIBOCR_API void config_set_parameter_bool(ocr_engine_config_ptr config, const char* key, bool value);
    LIBOCR_API void config_set_parameter_float(ocr_engine_config_ptr config, const char* key, float value);
    LIBOCR_API void config_set_parameter_double(ocr_engine_config_ptr config, const char* key, double value);
    LIBOCR_API void config_set_parameter_string(ocr_engine_config_ptr config, const char* key, const char* value, int value_size);
    LIBOCR_API void config_get_parameter(ocr_engine_config_ptr config, const char* key, char* buff, int buff_size);
    LIBOCR_API void config_get_parameter_int(ocr_engine_config_ptr config, const char* key, int* value);
    LIBOCR_API void config_get_parameter_bool(ocr_engine_config_ptr config, const char* key, bool* value);
    LIBOCR_API void config_get_parameter_float(ocr_engine_config_ptr config, const char* key, float* value);
    LIBOCR_API void config_get_parameter_double(ocr_engine_config_ptr config, const char* key, double* value);
    LIBOCR_API void config_get_parameter_string(ocr_engine_config_ptr config, const char* key, char* buff, int buff_size);
    LIBOCR_API void engine_config_destroy(ocr_engine_config_ptr config);

    struct ocr_engine;
    typedef struct ocr_engine ocr_engine_t;
    typedef ocr_engine_t* ocr_engine_ptr;

    LIBOCR_API ocr_engine_ptr engine_create();
    LIBOCR_API void engine_destroy(ocr_engine_ptr engine);
    LIBOCR_API void engine_set_lang(ocr_engine_ptr engine, const char* lang);
    LIBOCR_API void engine_set_image(ocr_engine_ptr engine, int width, int height, const char* image_data, int image_data_size);
    LIBOCR_API void engine_set_image_rgba(ocr_engine_ptr engine, int width, int height, const char* image_data, unsigned int row_pitch);
    LIBOCR_API void engine_set_image_file(ocr_engine_ptr engine, const char* image_file);
    LIBOCR_API void engine_set_image_file_data(ocr_engine_ptr engine, const char* image_data, int image_data_size);

#endif

    LIBOCR_API int ocr(const char* image_data, int image_data_size, char* result, int result_size);
    LIBOCR_API int ocr_image_data(int image_width, int image_height, const char* image_data, int image_data_size, char* result, int result_size);
    LIBOCR_API int ocr_image_data_rgba(int image_width, int image_height, const char* image_data, unsigned int row_pitch, char* result, int result_size);
    LIBOCR_API int ocr_file_data(const char* image_data, int image_data_size, char* result, int result_size);
    LIBOCR_API int ocr_file_path(const char* image_file, char* result, int result_size);
    // allocate memory
    LIBOCR_API const char* ocr_file(const char* file_path, int file_size);
    LIBOCR_API const char* ocr_image(int image_width, int image_height, const char* image_data, int image_data_size);
    // free memory
    LIBOCR_API void free_char(char* p);

#ifdef __cplusplus
}
#endif