#include <iomanip>
#include <iostream>
#include <locale>
#include <Windows.h> 
#include <string>
#include <exception>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    long double mon;
    long double currency_rate = 70;

    std::locale locale_1("en_US.UTF-8");
    std::cin.imbue(locale_1);

    std::locale locale_2("ru_RU.utf8");
    std::cout.imbue(locale_2);

    std::cin >> std::get_money(mon);
    mon *= currency_rate;
    std::cout << std::showbase << std::put_money(mon, false);

    return 0;
}
