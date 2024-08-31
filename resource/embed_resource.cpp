#include "embed_resource.h"
#include <map>
#define str(x) #x

const uint8_t define_flag[] = { "resource status: {false}\0" };

#define Opt(name, size, define_name) const uint8_t define_name[size + 1] = { "resource:{" str(name) "}" };
list_of_resources
#undef Opt

std::map<std::string, libocr::res_data> res_map = {
#define Opt(name, size, define_name) { str(name), { define_name, size } },
    list_of_resources
#undef Opt
};

libocr::res_data libocr::from_resource_load_file(std::string file_name)
{
    if (res_map.find(file_name) == res_map.end())
        return libocr::res_data();
    return res_map[file_name];
}
std::string libocr::resource_changed_flag()
{
    return std::string((const char*)define_flag, sizeof(define_flag));
}
