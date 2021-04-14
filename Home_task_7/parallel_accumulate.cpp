#include <future>
#include <cmath>
#include <thread>
#include <chrono>
#include <random>
#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int N = 10000;
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
	auto time() {
		auto end = clock_t::now();
		auto temp = end;
		for (size_t i = 0; i < size(v); i += 2) { //вычитаем перерывы
			if (i + 1 > size(v)) { // можно отключить таймер на паузе
				end -= temp - v[i];
				break;
			}
			end -= v[i + 1] - v[i];

		}
		return std::chrono::duration_cast <
			std::chrono::milliseconds> (end - m_begin).count();
	}

	Timer() : m_begin(clock_t::now()) {}
	~Timer()
	{
		//auto end = clock_t::now();
		//auto temp = end;
		//for (size_t i = 0; i < size(v); i += 2) { //вычитаем перерывы
		//	if (i + 1 > size(v)) { // можно отключить таймер на паузе
		//		end -= temp - v[i];
		//		break;
		//	}
		//	end -= v[i + 1] - v[i];
		//}
		//std::cout << "milliseconds	" << std::chrono::duration_cast <
		//	std::chrono::milliseconds> (end - m_begin).count() << std::endl;
	}

private:
	time_point_t m_begin;
	std::vector <time_point_t> v; // вектор точек остановок и включений
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int n)
{
	
	const std::size_t length = std::distance(first, last);

	if (n == 1 or length <= 3)
	{
		return std::accumulate(first, last, init);
	}
	else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < T > first_half_result =
			std::async(parallel_accumulate < Iterator, T >, first, middle, init, n / 2);

		T second_half_result = parallel_accumulate(middle, last, T(), n / 2);

		return first_half_result.get() + second_half_result;
	}
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");

	
	std::ofstream fout("D:\\Alex\\FOPF\\Прога\\C++\\Семинар7\\output.txt");
	//int n;
	//std::cout << "введите количество потоков" << std::endl;
	//std::cin >> n;

	std::vector < int > v(10e6);

	std::iota(v.begin(), v.end(), 1);
	int a = std::thread::hardware_concurrency();
	std::cout << a;
	/*{
		Timer t;
		std::cout << parallel_accumulate(v.begin(), v.end(), 0, n) << std::endl;
	}*/
	for (size_t i = 1; i < 10; i++)
	{
		std::cout << "Number of threads = " << i << "\t";
		Timer t;
		parallel_accumulate(v.begin(), v.end(), 0, i);
		auto a = t.time();
		std::cout << a << std::endl;
		fout << i <<"\t" << a << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}
