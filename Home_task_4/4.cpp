
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <set>

void Printvc(std::vector<int> &vc) {
	for (auto i : vc) {
		std::cout << i << "\t";
	};
	std::cout << std::endl;
};
bool isPrime(int n) {
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;   
}

int main()
{
	setlocale(LC_ALL, "ru");

	int n = 10;
    std::vector<int> p1;
	for (size_t i = 0; i < n; i++){ // создаём последовательность
		p1.push_back((rand() % 10) + 1);
	}

	std::cout << "введите ещё три числа \n";
	for (size_t i = 0; i < 3; i++) { // +3
		p1.push_back((rand() % 10) + 1);
	}

	std::random_shuffle(p1.begin(), p1.end()); // перемешаем

	//std::sort(p1.begin(), p1.end());  // сортируем
	Printvc(p1);

	std::vector<int> p_temp;
	std::set <int> s_temp;
	for (auto i : p1) { // сложно убираем дубликаты, потому что не знаю, как это сделать без сортировки
		auto a = s_temp.insert(i);
		if (a.second)
			p_temp.push_back(i);
	}
	p1 = p_temp;
	//p1.erase(std::unique(p1.begin(), p1.end()), p1.end()); // убираем соседние дубликаты, потому что не помню, можно ли без сортировки
	Printvc(p1);

	int k = 0;
	for (auto i : p1) { // количество нечётных
		if (i % 2 == 1)
			k++;
	};

	std::vector<int>::iterator min = std::min_element(p1.begin(), p1.end()); // почему-то думал, что должен возвращаться элемент, а не указатель
	std::vector<int>::iterator max = std::max_element(p1.begin(), p1.end()); // максимальный

	for (auto i : p1) { // ищем простые
		if (isPrime(i))
			std::cout << "простое " << i << std::endl;
	}

	std::for_each(p1.begin(), p1.end(), [](int& n) { n*=n; }); // возводим в квадраты

	std::vector<int> p2;
	for (size_t i = 0; i < p1.size(); i++) { // создаём последовательность 2
		p2.push_back((rand() % 10) + 1);
	}

	int b = 0;
	std::for_each(p2.begin(), p2.end(), [&b](int &n) {b += n; }); // сумма чисел во втором

	for (size_t i = 0; i < int(p2.size()/3); i++){ // меняем треть элементов на 1
		p2[i] = 1;
	}


	std::vector<int> p3 = p1; // создаём третий массив
	for (size_t i = 0; i < p1.size(); i++){
		p3[i] -= p2[i];
	}

	std::for_each(p3.begin(), p3.end(), [](int& n) { if (n < 0) n = 0; }); // заменяем отрицательные на нули

	remove_if(p3.begin(), p3.end(), [](int& n) { if (n == 0) return true; return false; }); // удаляем нулевые

	reverse(p3.begin(), p3.end()); // сортируем в обратном порядке

	nth_element(p3.begin(), p3.end() - 3, p3.end()); // пересортируем относительно N-3 элемента

	/* самые большие элементы  *(p3.end()-1)	*(p3.end() -2 )	*(p3.end() - 3) */

	std::sort(p1.begin(), p1.end()); // сортируем 1 и 2 массивы
	std::sort(p2.begin(), p2.end());

	std::vector<int> p4;
	std::merge(p1.begin(), p1.end(), p2.begin(), p2.end(), std::back_inserter(p4)); // слияние двух массивов в 4-ый

	const auto r = equal_range(p4.begin(), p4.end(), 1); // диапазон для упорядоченной вставки 1
	
	Printvc(p1);
	Printvc(p2);
	Printvc(p3);
	Printvc(p4);
	return 0;
}

