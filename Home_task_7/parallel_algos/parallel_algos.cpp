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
#include <execution>
#include<numeric>
#include <vector>

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



int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	std::ofstream fout("D:\\Alex\\FOPF\\Прога\\C++\\Семинар7\\output_algos.txt"); // to write in file
	std::vector < int > v1(10e5), v2(10e5);

	for (size_t i = 0; i < v1.size(); i++)
	{
		v1[i] = v2[2] = rand() % 100;
	}

	{
		Timer t;
		std::sort(std::execution::par_unseq, v1.begin(), v1.end()); //parallel_sort
		auto a = t.time();
		std::cout << "parallel_sort" << "\t" << a << std::endl;
		fout << "parallel_sort" << "\t" << a << std::endl;
	}
	{
		Timer t;
		std::sort(v2.begin(), v2.end()); // sequetnial_sort
		auto a = t.time();
		std::cout << "sequetnial_sort" << "\t" << a << std::endl;
		fout << "sequetnial_sort" << "\t" << a << std::endl;
	}
	for (size_t i = 0; i < 10e6; i++)
	{
		v1.push_back(rand() % 100);
	}
	v2 = v1;
	{
		Timer t;
		std::fill(std::execution::par_unseq, v2.begin(), v2.end(), -1); // parallel_fill
		auto a = t.time();
		std::cout << "parallel_fill" << "\t" << a << std::endl;
		fout << "parallel_fill" << "\t" << a << std::endl;
	}
	{
		Timer t;
		std::fill(v1.begin(), v1.end(), -1);
		auto a = t.time();
		std::cout << "sequetnial_fill" << "\t" << a << std::endl; // sequetnial_fill
		fout << "sequetnial_fill" << "\t" << a << std::endl;
	}
	

	for (size_t i = 0; i < v1.size(); i++)
	{
		v1[i] = v2[2] = rand() % 20;
	}
	
	{
		Timer t;
		std::replace(std::execution::par_unseq, v1.begin(), v1.end(), 8, 88); // parallel_replace
		auto a = t.time();
		std::cout << "parallel_replace" << "\t" << a << std::endl;
		fout << "parallel_replace" << "\t" << a << std::endl;
	}
	{
		Timer t;
		std::fill(v2.begin(), v2.end(), -1); // sequetnial_replace
		auto a = t.time();
		std::cout << "sequetnial_replace" << "\t" << a << std::endl;
		fout << "sequetnial_replace" << "\t" << a << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}
