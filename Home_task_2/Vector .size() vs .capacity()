#include <vector>
#include <iostream>

void foo(std::vector<int> v) {
	std::cout << "size " << v.size() << "\n"
		<< "capacity " << v.capacity() << "\n" << std::endl;
	std::cout << "v = { ";
	for (int n : v) {
		std::cout << n << ", ";
	}
	std::cout << "}; \n";
}

void printStack(const std::vector<int>& stack)
{
	for (const auto& element : stack)
		std::cout << element << ' ';
	std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
}


int main() {
	std::vector<int> stack;

	stack.reserve(7); // устанавливаем ёмкость (как минимум), равную 7
	printStack(stack);

	stack.push_back(7);
	printStack(stack);

	std::cout << "-----------------------------------------------------------------------------\n";

	std::vector<int> v;

	v.reserve(7); 
	foo(v);

	v.push_back(7);
	foo(v);


	return 0;
}
