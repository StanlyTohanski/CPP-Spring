
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

    const std::regex regular(R"(([ ]?|\d{1,4}\.\d{1,2}\.[1-31])|([0-2][0-4]:[0-5][0-9]:[0-5][0-9][ ]))");

    std::ofstream out("D:\\Alex\\FOPF\\Прога\\C++\\Семинар5\\output.txt");
    std::ifstream in("D:\\Alex\\FOPF\\Прога\\C++\\Семинар5\\input.txt");


    while (in) {
        std::string tmp;
        std::getline(in, tmp);
        std::cout << "строка: \t" << tmp << std::endl;
        if (std::regex_search(tmp, regular)) {
            const std::vector<std::smatch> full_match{
            std::sregex_iterator{tmp.begin(), tmp.end(), regular}, 
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
