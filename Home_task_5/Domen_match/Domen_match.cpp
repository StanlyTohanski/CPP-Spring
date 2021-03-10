
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <cstring>
#include <cassert>
#include <string_view>

bool is_valid(std::string & str) {

    return true;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    //const std::regex regular(R"(\w+\.?\w*(@\w+\.[[:alpha:]]+))");
    const std::regex regular(R"([ [:alnum:]]\w+\.?\w*(@\w+\.[[:alpha:]]+))");
    std::ofstream out("D:\\Alex\\FOPF\\Прога\\C++\\Семинар5\\output.txt");
    std::ifstream in("D:\\Alex\\FOPF\\Прога\\C++\\Семинар5\\input.txt");


    while (in) {
        std::string tmp;
        std::getline(in, tmp);
        std::cout << "строка: \t" << tmp << std::endl;
        if (std::regex_search(tmp, regular)) {
            const std::vector<std::smatch> full_match{
            std::sregex_iterator{tmp.begin(), tmp.end(), regular}, // Mark `0` here i.e. whole regex match
            std::sregex_iterator{}
            };
            for (auto i : full_match){
                std::cout << i.str(0) << "\t" << i.str(1) << '\n';
            }
        }
        else { std::cout << "не нашёл \n "; }


    }
    return 0;
}
