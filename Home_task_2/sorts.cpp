#include <vector>
#include <iostream>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
const int n = 100000;
std::vector<int> massive(n);

void foo(std::vector<int> &v) {
	std::cout << "size " << v.size() << "\n"
		<< "capacity " << v.capacity() << "\n" << std::endl;
}

template<typename T>
void fill(T &mass) {
	int k = 0;
	for (int i : mass){
		i = ::massive[k];
		k++;
	}
}

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

	Timer() : m_begin(clock_t::now()) {}
	~Timer()
	{
		auto end = clock_t::now();
		auto temp = end;
		for (size_t i = 0; i < size(v); i += 2) { //вычитаем перерывы
			if (i + 1 > size(v)) { // можно отключить таймер на паузе
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

int main() {
	for (int n : massive) {
		n = rand() % 400;
	}

	std::vector<int> vector(n);
	fill(vector);
	{
		std::cout << "vector_std_sort\t"; // std::sort
		Timer t;
		std::sort(begin(vector), end(vector));
	}
	std::cout << std::endl;

	std::array<int, n> array;
	fill(array);
	{	
		std::cout << "array_std_sort\t";
		Timer t;
		std::sort(array.begin(), array.end());
	}
	std::cout << std::endl;

	std::deque<int> deque(n);
	fill(deque);
	{
		std::cout << "deque_std_sort\t";
		Timer t;
		std::sort(begin(deque), end(deque));
	}
	std::cout << std::endl;

	std::list<int> list(n);
	fill(list);
	{
		std::cout << "list_std_sort\t"; // сортировать std::list нельзя с помощью std::sort, 
		Timer t;			// т.к. ему требуется итератор со случайным доступом, 
		list.sort();			// а у list только на один элемент вперёд или назад за раз				   
	}
	std::cout << std::endl;

	std::forward_list<int> forward_list(n);
	fill(forward_list);
	{
		std::cout << "forward_list_std_sort\t"; // то же, что и с std::list
		Timer t;
		forward_list.sort();			
	}
	std::cout << std::endl;

	return 0;
}
