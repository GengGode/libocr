#include <filesystem>
#include <fstream>
#include <map>
#include <regex>
#include <string>

#include <iostream>

#define def_to_str(x) #x

static std::map<std::string, size_t> res_map = {
#define Opt(name, size, define_name) { def_to_str(name), size },
    list_of_resources
#undef Opt
};

std::vector<std::match_results<std::string::const_iterator>> regex_match_all(const std::string& str, const std::regex& re)
{
    std::vector<std::match_results<std::string::const_iterator>> matches;
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), re);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        matches.push_back(*i);
    }
    return matches;
}


int main(int argc, char* argv[])
{
    if (argc != 3)
        return -1;
    // lib path and resource path
    auto lib_file = std::filesystem::path(argv[1]);
    auto resource_path = std::filesystem::path(argv[2]);
    if (!std::filesystem::exists(lib_file) || !std::filesystem::exists(resource_path))
        return -2;

    std::cout << "lib_file: " << lib_file << std::endl;
    std::cout << "resource_path: " << resource_path << std::endl;

    std::ifstream original_lib_file(lib_file, std::ios::binary);
    std::ofstream new_lib_file(lib_file.string() + ".new", std::ios::binary);

    if (!original_lib_file.is_open() || !new_lib_file.is_open())
    {
        std::cout << "original_lib_file or new_lib_file is not open" << std::endl;
        return -3;
    }

    if (!std::filesystem::is_directory(resource_path))
    {
        std::cout << "resource_path is not a directory" << std::endl;
        return -4;
    }

    for (auto& [res_file, res_size] : res_map)
    {
        auto res_path = resource_path / res_file;
        if (!std::filesystem::exists(res_path))
            return -5;
    }

    std::string lib_content((std::istreambuf_iterator<char>(original_lib_file)), std::istreambuf_iterator<char>());
    std::string new_lib_content = lib_content;

    original_lib_file.close();

    std::regex resource_changed_flag_regex(R"(resource status: \{(.+?)\})");
    std::smatch changed_flag_match;
    size_t changed_flag_pointer = 0;
    auto changed_flag_matches = regex_match_all(lib_content, resource_changed_flag_regex);
    if (changed_flag_matches.size() == 0)
    {
        std::cout << "changed_flag_matches.size() == 0" << std::endl;
        return -6;
    }
    for (auto& changed_flag_result : changed_flag_matches)
    {
        if (changed_flag_result[1].str() == "true")
        {
            std::cout << "resource status: true" << std::endl;
            return 0;
        }
        if (changed_flag_result[1].str() != "false")
        {
            std::cout << "changed_flag_result[1].str() != false" << std::endl;
            return -7;
        }

        changed_flag_pointer = changed_flag_result.position();
        std::cout << "changed_flag_pointer: " << changed_flag_pointer << std::endl;
    }

    std::regex resource_regex(R"(resource:\{(.+?)\})");
    std::smatch match;
    std::map<std::string, size_t> resource_pointers;
    auto matches = regex_match_all(lib_content, resource_regex);
    for (auto& match : matches)
    {
        auto resource_name = match[1].str();
        auto pointer = match.position();
        resource_pointers[resource_name] = pointer;
        std::cout << "resource_name: " << resource_name << " pointer: " << pointer << std::endl;
    }

    for (auto& [res_file, res_size] : res_map)
    {
        auto res_path = resource_path / res_file;
        std::ifstream ifs_res(res_path, std::ios::binary);
        if (!ifs_res.is_open())
        {
            std::cout << "res_path: " << res_path << std::endl;
            return -6;
        }
        std::string res_content((std::istreambuf_iterator<char>(ifs_res)), std::istreambuf_iterator<char>());
        std::cout << "res_content.size(): " << res_content.size() << " res_size: " << res_size << std::endl;
        if (res_content.size() != res_size)
        {
            return -7;
        }
        auto pointer = resource_pointers[res_file];
        new_lib_content.replace(pointer, res_size, res_content);

        std::cout << "replace position: " << pointer << " resource_name: " << res_file << std::endl;
    }

    if (changed_flag_pointer == 0)
    {
        std::cout << "changed_flag_pointer is 0" << std::endl;
        return -8;
    }
    new_lib_content.replace(changed_flag_pointer, 23, "resource status: {true}");

    new_lib_file << new_lib_content;
    new_lib_file.close();

    // rename original to .old
    std::filesystem::rename(lib_file, lib_file.string() + ".old");
    // rename new to original
    std::filesystem::rename(lib_file.string() + ".new", lib_file);
    return 0;
}
