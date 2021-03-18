#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

int main()
{
    auto path1 = std::filesystem::path("D:\\Alex\\FOPF\\Прога\\C++\\Семинар6\\test.txt"); 
    std::ofstream fout("D:\\Alex\\FOPF\\Прога\\C++\\Семинар6\\output.txt");
    std::ifstream fin(path1.string(), std::ios::in);

    bool in_string = false; // внутри открытой строки
    bool multiline_comment = false; // внутри многострочного(опционально) комментария


    while (fin) {
        std::string tmp_in;
        std::string tmp_out;
        std::getline(fin, tmp_in);
        for (size_t i = 0; i < tmp_in.length(); i++) {
            if (tmp_in[i] == '/' && tmp_in[i + 1] == '*') { // многострочный(опционально) коммент начался
                multiline_comment = true;
                i++;
                continue;
            }

            if ( tmp_in[i + 1] == '/' && tmp_in[i] == '*') { // многострочный(опционально) коммент закончился
                if (multiline_comment = true) { // если поставить это условие третьим в предыдущий if, то будет ошибка по непонятной причине
                    multiline_comment = false;
                    i++;
                    continue;
                }
            }

            if (tmp_in[i] == '"') { // состояние открытой/закрытой строки
                in_string = !in_string;
            }

            if (tmp_in[i] == '/' && tmp_in[i + 1] == '/' && !in_string) {   // внтури открытой строки за коммент не считаем
                break;
            }

            if (!multiline_comment) // запись в строку вывода поэлементно
                tmp_out += tmp_in[i];
        }
        
        if (tmp_out != "\n") // запись строки без комментов в файл
                fout << tmp_out << std::endl;
        
    }
    
    return 0;
}
