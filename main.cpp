// #include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	std::iterator
// 	return (0);
// }


#include <vector>
#include <iostream>
#include <iterator>
#include "vector.hpp"
#include <memory>
#include <typeinfo>
#include <type_traits>
#include "utility.hpp"
#include <map>
#include <exception>

int main()
{
	
	// std::vector<int> a(10, 20);
	// std::cout << "size: " << a.size() << ", capacity: " << a.capacity() <<"\n";
	// a.push_back(222);
	// std::cout << "size: " << a.size() << ", capacity: " << a.capacity() <<"\n";
	// for(int i = 0; i < 10; ++i)
	// 	a.push_back(i*10);
	// std::cout << "size: " << a.size() << ", capacity: " << a.capacity() <<"\n";
	// std::cout << "===============================================\n";


	// std::vector<int> b;
	// std::cout << "size: " << b.size() << ", capacity: " << b.capacity() <<"\n";
	// b.push_back(1);
	// std::cout << "size: " << b.size() << ", capacity: " << b.capacity() <<"\n";
	// for(int i = 0; i < 10; ++i)
	// {
	// 	b.push_back(i*10);
	// 	std::cout << "size: " << b.size() << ", capacity: " << b.capacity() <<"\n";
	// }


	// std::vector<int> a(10 , 10);
	// std::vector<int> b(a);

	// std::cout << &a << "\n";
	// std::cout << &b << "\n";
	// std::cout << &(*a.begin()) << "\n";
	// std::cout << &(*b.begin()) << "\n";




	// *ait;


	// ait.operator->();


	// std::vector<int> b(10, 10);
	// std::vector<int>::const_iterator bi = b.begin();

	// std::vector<int> c;
	// std::cout << typeid(std::vector<int>::const_iterator::value_type).name() << "\n";
	// std::cout << typeid(char).name() << "\n";

	// std::cout << "====================\n";

	// std::vector<int> va;
	// for (int i = 0; i < 10; ++i)
	// 	va.push_back(i + 1);
	// std::vector<int>::iterator vai(va.begin()), vaii;

	// vaii = vai + 5;
	// std::cout << *vaii << "\n";
	// std::cout << typeid(vai + 5).name() << "\n";

	// vaii = 5 + vai;
	// std::cout << *vaii << "\n";
	// std::cout << *(5 + vai) << "\n";

	// (vai == vaii) ? std::cout << "EQUAL\n" : std::cout << "DIFFER\n";
	// (vai != vaii) ? std::cout << "DIFFER\n" : std::cout << "EQUAL\n";
	// (vai < vaii) ? std::cout << "DIFFER\n" : std::cout << "EQUAL\n";
	// (vai > vaii) ? std::cout << "DIFFER\n" : std::cout << "EQUAL\n";
	// (vai <= vaii) ? std::cout << "DIFFER\n" : std::cout << "EQUAL\n";
	// (vai >= vaii) ? std::cout << "DIFFER\n" : std::cout << "EQUAL\n";


	// std::cout << *vai << "\n";
	// *vai = 4242;
	// std::cout << *vai << "\n";
	// std::cout << vai.operator->() << "\n";

	// std::cout << *(vai++) << "\n";
	// std::cout << *(++vai) << "\n";
	// *vai++;


	// vai--;
	// --vai;
	// *vai--;

	return 0;
}