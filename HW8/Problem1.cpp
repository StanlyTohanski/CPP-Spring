#include <iostream>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>


const int NumT = 8;
const int NumIt = 400000;

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;

    Timer() : m_begin(clock_t::now()) {}

    ~Timer()
    {
        auto end = clock_t::now();
        std::cout << std::chrono::duration_cast <std::chrono::milliseconds>(end - m_begin).count() << " milliseconds" << std::endl;

    }
private:
    time_point_t m_begin;
};

int random(int range_min, int range_max) {
    return rand() % (range_max - range_min + 1) + range_min;
}

double MC(size_t iters) { // Монте Карло
    srand((unsigned)time(0));
    int counter = 0;
    int side = 1000;
    int sqside = side * side;
    for (int i = 0; i < iters; ++i) {
        int x = random(0, side);
        int y = random(0, side);

        if ((x * x + y * y) < sqside) ++counter;
    }
    return double(counter) / iters * 4;
}


int main() {

    {
        Timer t;
        std::vector<double> result;
        std::vector<std::thread> vec_thr; // посчитаем пи несколько раз
        std::mutex m;
        for (int i = 0; i < NumT; ++i) { // создаём locked задачи
            size_t counter = NumIt;
            vec_thr.emplace_back([&result, &m, counter]() {
                double pi = MC(counter);
                std::lock_guard<std::mutex> lock(m);
                result.emplace_back(pi);
                });
        }
        for (auto& thread : vec_thr) { // ждём, когда выполнятся
            thread.join();
        }
        std::cout << std::accumulate(result.begin(), result.end(), 0.0) / result.size() << std::endl; // через ср. арифм
    }

    return 0;
}
