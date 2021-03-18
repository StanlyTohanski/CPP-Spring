#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
const int n = 10;

int main()
{
    setlocale(LC_ALL, "Rus");
    auto path = std::filesystem::current_path() / "file.txt";
    std::ofstream fout(path, std::ios::out);

    std::string str = "Hello, world! " + std::to_string(0) + " let's live!"; // шаблон строки
    
    for (size_t i = 0; i < n; i++) { // записываем в файл
        std::string str = "Hello, world! " + std::to_string(i+1) + " let's live!";
        fout << str << std::endl;
        }
    fout.close(); 

    std::ifstream fin(path, std::ios::in);
    std::string tmp;
    std::getline(fin, tmp);
    int length = fin.tellg(); // длина строки

    std::cout << length << "\t" << str.length() << std::endl;

    std::cout << "Всего " << n << " строк. Впишите номер искомой строки"<< std::endl;
    
    while (std::cin) {
        int num;
        std::cin >> num;
        //fin.seekg(fin.cur + str.length()*n);
        std::string tmp1;
        fin.seekg(0);
        fin.seekg(length * (num-1), std::ios::beg); //ставим курсор в начало нужной строки
        std::getline(fin, tmp1);
        std::cout << tmp1 << std::endl;
    }
    

   
    
    return 0;
}
