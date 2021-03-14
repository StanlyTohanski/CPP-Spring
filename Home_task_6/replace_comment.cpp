
#include <string>
#include <regex>
#include <fstream>
#include <filesystem>

int main()
{

    auto path1 = std::filesystem::path("D:/Alex/FOPF/Прога/C++/Семинар6/test.txt"); 
    std::ofstream out("D:\\Alex\\FOPF\\Прога\\C++\\Семинар6\\output.txt");
    const std::regex regular(R"(/*.**/)");    
    std::fstream fin(path1.string(), std::ios::in);

    while (fin) {
        std::string tmp;
        std::string tmp1;
        std::getline(fin, tmp);
        std::regex_replace(tmp1, tmp.begin(), tmp.end(), regular, "");
        out << tmp1 << "\n";
    }
    
    return 0;
}
