//
// Created by YuSuiXian on 2023/6/17.
//

#include <iostream>
#include <fstream>
#include <Windows.h>

// 全局libocr.dll句柄
HINSTANCE g_hDll = NULL;

typedef int(*OCR_FILE_DATA)(const char *image_data, int image_data_size, char *result, int result_size);
OCR_FILE_DATA g_ocr_file_data = NULL;
struct libocr
{
    static int load()
    {
        // 1.加载动态链接库
        g_hDll = LoadLibraryA("libocr.dll");
        if (NULL == g_hDll)
        {
            std::cout << "LoadLibraryA failed" << std::endl;
            return -1;
        }

        // 2.获取函数地址
        g_ocr_file_data = (OCR_FILE_DATA)GetProcAddress(g_hDll, "ocr_file_data");
        if (NULL == g_ocr_file_data)
        {
            std::cout << "GetProcAddress failed" << std::endl;
            return -1;
        }
        return 0;
    }

    static int ocr_file_data(const char *image_data, int image_data_size, char *result, int result_size)
    {
        if (NULL == g_ocr_file_data)
        {
            std::cout << "GetProcAddress failed" << std::endl;
            return -1;
        }
        return g_ocr_file_data(image_data, image_data_size, result, result_size);
    }
};

int Test_File()
{
    std::string image_path = "test.png";
    std::string result="「诤言」的教导";
    std::ifstream ifs(image_path, std::ios::binary);
    if (!ifs.is_open())
    {
        std::cout << "open file failed" << std::endl;
        return -1;
    }
    std::string image_data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    std::string text;
    //=========================================================================
    {
        char *result_buff = new char[1024];
        //int res= libocr::ocr_file_path(image_path.c_str(), result_buff, 1024);
        int res= libocr::ocr_file_data(image_data.c_str(), image_data.size(), result_buff, 1024);
        if (res == 0) {
            text = std::string(result_buff);
        }
        else
        {
            std::cout << "error code:" << res << " = file:" << image_path << std::endl;
        }
        //libocr::free_char(result);
        delete[] result_buff;
    }
    //=========================================================================
    std::cout << text << std::endl;
    if (text != result)
    {
        static bool first = true;
        if (first) {
            first = false;
            std::cout << "text:" << text << " != " << result << std::endl;
        }
        // std::cout << "error code:" << " = file:" << image_path << std::endl;
        return -1;
    }
    return 0;
}

#include <windows.h>
#include <psapi.h>

int main(int argc,char* argv[]) {
    libocr::load();
    system("chcp 65001");
    int test_cycle = 200;

    int test_count = 0;
    int test_error = 0;

    int mem_used_before              = 0;
    int mem_used_after               = 0;

    PROCESS_MEMORY_COUNTERS pmc;
    auto                    mem_info = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    if (mem_info) {
        mem_used_before = pmc.WorkingSetSize;
    }

    for (int i = 0; i < test_cycle; i++) {
        test_count++;

        int res = Test_File();

        // 当前系统内存占用
        mem_info = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        if (mem_info) {
            mem_used_after = pmc.WorkingSetSize;
        }

        if (res != 0) {
            test_error++;
        }
        double mem_used = (mem_used_after - mem_used_before) / 1024.0 / 1024.0;
        std::cout << "test_count:" << test_count << " test_error:" << test_error << " mem_used:" << mem_used
                  << std::endl;
    }
    //std::cout << "test_count:" << test_count << " test_error:" << test_error << std::endl;
    return 0;
}