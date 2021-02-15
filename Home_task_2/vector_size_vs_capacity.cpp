#include <vector>
#include <iostream>

void foo(std::vector<int> &v) {
	std::cout << "size " << v.size() << "\n"
		  << "capacity " << v.capacity() << "\n" << std::endl;
}


int main() {


	std::vector<int> v;
	foo(v);
	for (size_t i = 0; i < 20; i++)	{
		v.push_back(i);
		foo(v);
	} // заметим закономерность: ёмкость вектора увеличивается на целую часть 50%-ов в момент, когда не хватает места на новый элемент.
	  // + resize() не увеличивает ёмкость.

	std::vector<int> k;
	foo(k);
	k.reserve(20);
	foo(k); // ёмкость увеличивается(не уменьшается) до заданной, сколько бы уже ни было выделено и, 
		// если хватает свободного пространства и не превышено предельное значение

	std::vector<int> a(100);
	foo(a);
	a.reserve(a.max_size()-2); // Возникло необработанное исключение по адресу 0x760DA8B2 в Vector(2).exe: 
				   // исключение Microsoft C++ : std::bad_array_new_length 
	foo(a);			   // столько подряд свободного пространства нет

	

	return 0;
}
