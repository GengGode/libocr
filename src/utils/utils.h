//
// Created by GengG on 2022/11/9.
//

#ifndef LIBOCR_UTILS_H
#define LIBOCR_UTILS_H
#include "include.h"
namespace libocr::utils
{
    inline std::string get_input_name(Ort::Session* session)
    {
        size_t num_input_nodes = session->GetInputCount();
        if (num_input_nodes == 0)
        {
            throw std::runtime_error("This model does not have 1 input node.");
        }
        else
        {
            std::string input_name;
            Ort::AllocatorWithDefaultOptions allocator;
            {
                auto input_name_t = session->GetInputNameAllocated(0, allocator);
                input_name = input_name_t.get();
                //allocator.Free(&output_name_t);
            }
            return input_name;
        }
    }
    inline std::string get_output_name(Ort::Session* session)
    {
        size_t num_output_nodes = session->GetOutputCount();
        if (num_output_nodes == 0)
        {
            throw std::runtime_error("This model does not have 1 output node.");
        }
        else
        {
            std::string output_name;
            Ort::AllocatorWithDefaultOptions allocator;
            {
                auto output_name_t = session->GetOutputNameAllocated(0, allocator);
                output_name = output_name_t.get();
                //allocator.Free(&output_name_t);
            }
            return output_name;
        }
    }
    inline std::vector<int64_t> get_input_shape(Ort::Session* session)
    {
        size_t num_input_nodes = session->GetInputCount();
        if (num_input_nodes == 0)
        {
            throw std::runtime_error("This model does not have 1 input node.");
        }
        else
        {
            Ort::AllocatorWithDefaultOptions allocator;
            {
                auto input_node_info = session->GetInputTypeInfo(0);
                auto tensor_info = input_node_info.GetTensorTypeAndShapeInfo();
                auto input_shape = tensor_info.GetShape();
                return input_shape;
            }
        }
    }
    struct res_data_ptr
    {
        const void* data;
        size_t data_length;
    };
    inline res_data_ptr from_resource_load_onnx(int idr)
    {
        // Initialize session from Resource idr
#ifdef _LIB
        auto h_module = GetModuleHandle(NULL);
#else
#ifdef _UNICODE
        auto h_module = GetModuleHandle(L"libocr.dll");
#else
        auto h_module = GetModuleHandle("libocr.dll");
#endif
#endif
#ifdef _UNICODE
        HRSRC h_res = FindResource(h_module, MAKEINTRESOURCE(idr), L"Onnx");
#else
        HRSRC h_res = FindResource(h_module, MAKEINTRESOURCE(idr), "Onnx");
#endif
        if (h_res == 0) return res_data_ptr();
        HGLOBAL h_mem = LoadResource(h_module, h_res);
        if (h_mem == 0) return res_data_ptr();
        
        DWORD dw_size = SizeofResource(h_module, h_res);
        LPVOID lp_data = LockResource(h_mem);
        
        return { lp_data , dw_size };
    }
    inline res_data_ptr from_resource_load_txt(int idr)
    {
        // Initialize txt from Resource idr
#ifdef _LIB
        auto h_module = GetModuleHandle(NULL);
#else
#ifdef _UNICODE
        auto h_module = GetModuleHandle(L"libocr.dll");
#else
        auto h_module = GetModuleHandle("libocr.dll");
#endif
#endif
#ifdef _UNICODE
        HRSRC h_res = FindResource(h_module, MAKEINTRESOURCE(idr), L"Txt");
#else
        HRSRC h_res = FindResource(h_module, MAKEINTRESOURCE(idr), "Txt");
#endif
        if (h_res == 0) return res_data_ptr();
        HGLOBAL h_mem = LoadResource(h_module, h_res);
        if (h_mem == 0) return res_data_ptr();
        
        DWORD dw_size = SizeofResource(h_module, h_res);
        LPVOID lp_data = LockResource(h_mem);
        
        return { lp_data , dw_size };
    }
}
#endif //LIBOCR_UTILS_H
