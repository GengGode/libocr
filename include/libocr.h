//
// Created by GengG on 2022/11/9.
//
#ifdef LIBOCR_EXPORT
#define LIBOCR_API __declspec(dllexport)
#else
#define LIBOCR_API __declspec(dllimport)
#endif

#ifdef  __cplusplus
extern "C" {
#endif

// Path: inlcude\libocr.h
LIBOCR_API int ocr(const char *image_data, int image_data_size, char *result, int result_size);
LIBOCR_API int ocr_image_data(int image_width, int image_height, const char *image_data, int image_data_size, char *result, int result_size);
LIBOCR_API int ocr_file_data(const char *image_data, int image_data_size, char *result, int result_size);
LIBOCR_API int ocr_file(const char *image_file, char *result, int result_size);
// allocate memory
LIBOCR_API const char* ocr_rec(const char *file_path, int *file_size);
// free memory
LIBOCR_API void free_char(char *p);

#ifdef  __cplusplus
}
#endif

