#pragma once
#include <stdint.h>
#include <string>
namespace libocr
{
    struct res_data
    {
        const uint8_t* data;
        size_t size;
    };

    res_data from_resource_load_file(std::string file_name);

    std::string resource_changed_flag();
} // namespace libocr
