#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>
const int n = 10;
#include <boost/filesystem/operations.hpp>

inline std::string filestamp(const std::string& path) {
    std::time_t t = boost::filesystem::last_write_time(path);
    return std::asctime(std::localtime(&t));
}
namespace fs = std::filesystem;

void demo_status(const fs::path& p, fs::file_status s)
{
    switch (s.type())
    {
    case fs::file_type::none: std::cout << " has `not-evaluated-yet` type"; break;
    case fs::file_type::not_found: std::cout << " does not exist"; break;
    case fs::file_type::regular: std::cout << " regular file"; break;
    case fs::file_type::directory: std::cout << "  directory"; break;
    case fs::file_type::symlink: std::cout << "  symlink"; break;
    case fs::file_type::block: std::cout << " block device"; break;
    case fs::file_type::character: std::cout << "  character device"; break;
    case fs::file_type::fifo: std::cout << " named IPC pipe"; break;
    case fs::file_type::socket: std::cout << "  named IPC socket"; break;
    case fs::file_type::unknown: std::cout << " has `unknown` type"; break;
    default: std::cout << " has `implementation-defined` type"; break;
    }
    std::cout << '\n';
}
int main()
{
    setlocale(LC_ALL, "Rus");
    auto path = std::filesystem::current_path();
    for (auto& p : std::filesystem::directory_iterator(path)) {
        std::cout << "File name = " << p.path().filename().string() << '\n';
        std::cout << "File size = " << p.file_size() << "bytes"<< '\n';
        
        std::cout << "File type = ";
        demo_status(p.path(), fs::status(p.path()));
        
        std::cout << "File write time is " << filestamp(p.path().string()) << '\n';

    }
        
    

   
    
    return 0;
}
