
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

int main()
{
	setlocale(LC_ALL, "ru");

	int n = 100;
  std::vector<int> p1 (n);
	for (size_t i = 0; i < p1.size(); i++) { // создаём последовательность
	  p1.push_back(rand() % 100);
	}
  
	std::random_shuffle(p1.begin(), p1.end()); // перемешаем
  
	std::vector<int> p2 = p1;
  
	int i1 = 0;
	int i2 = 0;
	std::sort(p1.begin(), p1.end(), [&i1](int a, int b) {i1++; return a > b; });// сортируем
	std::nth_element(p2.begin(), p2.end() - 40, p2.end(), [&i2](int a, int b) {i2++; return a > b; }); // пересортируем относительно N-3 элемента
	
	std::cout << "для sort всего сравнений " << i1 << std::endl;
	std::cout << "для nth_element(1000-40) всего сравнений " << i2 << std::endl;

	return 0;
}

