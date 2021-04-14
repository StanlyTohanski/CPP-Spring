
#include <future>

#include <thread>

#include <random>
#include <exception>
#include <iostream>

#include <algorithm>
#include <iostream>
#include <vector>

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

	std::cout << " изначальный \n";
	std::vector < int > v(10);
	for (size_t i = 0; i < v.size(); i++)
	{
		v[i] = rand() % 100;
		std::cout << v[i] << " ";
	}

	parallel_for_each(std::begin(v), std::end(v), [](auto &i) { i = (i / 2); });
	std::cout << "\n изменённый \n";
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}

	

	system("pause");

	return EXIT_SUCCESS;
}

