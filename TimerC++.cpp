#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
class Timer 
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	void pause() { // остановить таймер
		v.push_back(clock_t::now());
		std::cout << "Pause" << std::endl;
	}
	void go_on() { // продолжить счёт времени таймера
		v.push_back(clock_t::now());
		std::cout << "Continue" << std::endl;
	}

	Timer(): m_begin(clock_t::now()) {}
	~Timer()
	{
		auto end = clock_t::now();
		auto temp = end;
		for (size_t i = 0; i < size(v); i+=2) { //вычитаем перерывы
			if (i + 1 > size(v)) {
				end -= temp - v[i];
				break;
			}
			end -= v[i + 1] - v[i];
			
		}
		std::cout << "milliseconds	" << std::chrono::duration_cast <
			std::chrono::milliseconds> (end - m_begin).count() << std::endl;		
	}

private:
	time_point_t m_begin;
	std::vector <time_point_t> v; // вектор точек остановок и включений
};


int main(int argc, char** argv)
{
	std::vector v(100000, 0);
	Timer t;
	for (size_t i = 0; i < size(v); i++) {
		v[i] = std::rand() % 20;
	}
	t.pause();
	for (size_t i = 0; i < size(v); i++) {
		v[i] = std::rand() % 30;
	}
	t.go_on();
	std::sort(std::begin(v), std::end(v));


	return 0;
}