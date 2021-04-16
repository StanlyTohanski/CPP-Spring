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
template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
	ptrdiff_t const range_length = last - first;
	if (!range_length)
		return;
	if (range_length == 1)
	{
		f(*first);
		return;
	}

	Iterator const mid = first + (range_length / 2);

	std::future<void> bgtask = std::async(&parallel_for_each<Iterator, Func>, first, mid, f);
	try
	{
		parallel_for_each(mid, last, f);
	}
	catch (...)
	{
		bgtask.wait();
		throw;
	}
	bgtask.get();
}


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	std::ofstream fout("D:\\Alex\\FOPF\\Прога\\C++\\Семинар7\\output_algos.txt"); // to write in file

	std::vector<int> xvalues(10e7, 1), yvalues(10e7, 1);
	for (size_t i = 0; i < xvalues.size(); i++)
	{
		xvalues[i] = yvalues[2] = rand() % 100;
	}
	{
		Timer t;
		int r1 = std::inner_product(xvalues.begin(), xvalues.end(), yvalues.begin(), 0); // inner_product
		auto a = t.time();
		std::cout << "inner_product" << "\t" << a << std::endl;
		fout << "inner_product" << "\t" << a << std::endl;
	}

	{
		Timer t;
		int result = std::transform_reduce( // transform_reduce
			std::execution::par,
			xvalues.begin(), xvalues.end(),
			yvalues.begin(), 0
		);
		auto a = t.time();
		std::cout << "transform_reduce" << "\t" << a << std::endl; 
		fout << "transform_reduce" << "\t" << a << std::endl;
	}

	std::vector < int > v1(10e2), v2(10e2);
	for (size_t i = 0; i < v1.size(); i++)
	{
		v1[i] = v2[2] = rand() % 100;
	}
	{
		Timer t;
		parallel_for_each(std::begin(v1), std::end(v1), [](auto& i) { i = (i / 2); }); // parallel_for_each
		auto a = t.time();
		std::cout << "parallel_for_each" << "\t" << a << std::endl;
		fout << "parallel_for_each" << "\t" << a << std::endl;
	}
	{
		Timer t;
		std::for_each(std::begin(v2), std::end(v2), [](auto& i) { i = (i / 2); }); // sequential_for_each
		auto a = t.time();
		std::cout << "sequential_for_each" << "\t" << a << std::endl;
		fout << "sequential_for_each" << "\t" << a << std::endl;
	}

	std::vector < int > v11(10e2), v22(10e2);

	for (size_t i = 0; i < v11.size(); i++)
	{
		v11[i] = v22[i] = rand() % 100;
	}
	{
		Timer t;
		std::cout << "inclusive sum: ";
		std::inclusive_scan(v11.begin(), v11.end(),
			std::ostream_iterator<int>(std::cout, " "));	 // inclusive_scan
		auto a = t.time();
		std::cout << "\n inclusive_scan" << "\t" << a << std::endl;
		fout << "\n inclusive_scan" << "\t" << a << std::endl;
	}
	{
		Timer t;
		std::cout << "partial_sum: ";
		std::partial_sum(v22.begin(), v22.end(),
			std::ostream_iterator<int>(std::cout, " ")); // partial_sum
		auto a = t.time();
		std::cout << "\n partial_sum" << "\t" << a << std::endl;
		fout << "\n partial_sum" << "\t" << a << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}
