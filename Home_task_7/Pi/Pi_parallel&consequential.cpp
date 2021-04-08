
#include <future>
#include <cmath>
#include <thread>
#include <chrono>
#include <random>
#include <exception>
#include <iostream>
int N = 10000;
int r = 10000;
int random_num()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> distr(0, r);

    /*for (size_t i = 0; i < 10; ++i){
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        std::cout.put(c).flush();
    }*/
    return distr(gen);
}
bool incircle(int pointx, int pointy, int r)
{
    if (std::pow((pointx - r),2) + std::pow((pointy - r),2) <= std::pow(r,2))
        return 1;
    return 0;
}

int func1()
{
    int Sc = 0;
    int pointx, pointy;
    for (size_t i = 0; i < N; i++)
    {
        pointx = random_num();
        pointy = random_num();
        if (incircle(pointx, pointy, r))
            Sc++;
    }
    return Sc;
}

int func2()
{
    int Sc = 0;
    int pointx, pointy;
    for (size_t i = 0; i < N; i++)
    {
        pointx = random_num();
        pointy = random_num();
        if (incircle(pointx, pointy, r))
            Sc++;
    }
    return Sc;
}


int main()
{
    // параллельно
    std::future<int> result1(std::async(func1));
    int result2 = func2();
    double Sc = static_cast<double>(result1.get() + result2);
    double Ss = 2*N;
    double Pi = Sc / Ss * 4;
    std::cout << "\n Pi = " << Pi
              << std::endl;
    // последовательно
    Sc = static_cast<double>(func1() + func2());
    Pi = Sc / Ss * 4;
    std::cout << "\n Pi = " << Pi
        << std::endl;
}


