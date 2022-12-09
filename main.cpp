// #include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include "map.hpp"
// 	#include "stack.hpp"
// 	#include "vector.hpp"
// #endif

// #include <stdlib.h>
// #include <time.h>

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


// int main(int argc, char** argv)
// {
// 	clock_t start, end;
// 	double duration;

// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	start = clock();
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
// 		map_int.insert(ft::make_pair(rand() , rand()));
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

// 	end = clock();
// 	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
// 	std::cout << "[time : " << duration<< "]\n";
// 	return (0);
// }

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <utility>
#include "vector.hpp"
#include "utility.hpp"
#include "map.hpp"
#include "stack.hpp"
#include <stdlib.h>



int main()
{

	int seed = 0;
	srand(reinterpret_cast<size_t>(&seed));

	std::vector<int>	_ori;
	ft::vector<int>		_my;



	std::cout << "\n\n====== VECTOR - PUSH_BACK TEST ======\n";
	unsigned int val;
	for(int i = 0; i < 40; ++i)
	{
		val = rand() % 50;
		_ori.push_back(val);
		_my.push_back(val);
	}
	std::vector<int>::iterator oit = _ori.begin();
	ft::vector<int>::iterator mit = _my.begin();
	std::cout << "original-";
	for(; oit != _ori.end(); ++oit)
		std::cout << *oit << ", ";
	std::cout << "\n      my-";
	for(; mit != _my.end(); ++ mit)
		std::cout << *mit << ", ";
	std::cout << "\n";
	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";


	std::cout << "\n\n====== VECTOR - POP_BACK TEST ======\n";
	for(int i = 0; i < 10; ++i)
	{
		_ori.pop_back();
		_my.pop_back();
	}
	std::cout << "original-";
	oit = _ori.begin();
	mit = _my.begin();
	for(; oit != _ori.end(); ++oit)
		std::cout << *oit << ", ";
	std::cout << "\n      my-";
	for(; mit != _my.end(); ++ mit)
		std::cout << *mit << ", ";
	std::cout << "\n";
	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";



	std::cout << "\n\n====== VECTOR - AT TEST ======\n";
	for(int i = 5; i < 14; ++i)
	{
		std::cout << "ori:" << _ori.at(i) << "";
		std::cout << " my :" << _my.at(i) << "\n";
	}

	std::cout << "\n\n====== VECTOR - [] OPERATOR TEST ======\n";
	for(int i = 5; i < 14; ++i)
	{
		std::cout << "ori:" << _ori[i] << "";
		std::cout << " my :" << _my[i] << "\n";
	}


	std::cout << "\n\n====== VECTOR - FRONT TEST ======\n";
	std::cout << "ori:" << _ori.front();
	std::cout << " my :" << _my.front() << "\n";



	std::cout << "\n\n====== VECTOR - BACK TEST ======\n";
	std::cout << "ori:" << _ori.back();
	std::cout << " my :" << _my.back() << "\n";



	std::cout << "\n\n====== VECTOR - DATA TEST ======\n";
	int* oriData = _ori.data();
	int* myData = _my.data();
		std::cout << "ori:";
	for(size_t i = 0; i  != _ori.size(); ++i)
		std::cout << oriData[i] << ", ";
	std::cout << "\n my:";
	for(size_t i = 0; i  != _ori.size(); ++i)
		std::cout << myData[i] << ", ";
	std::cout << "\n";




	std::cout << "\n\n====== VECTOR - REVERSE ITERATOR TEST ======\n";
	std::vector<int>::reverse_iterator orit = _ori.rbegin();
	ft::vector<int>::reverse_iterator mrit = _my.rbegin();

	std::cout << "ori:";
	for(; orit != _ori.rend(); ++orit)
		std::cout << *orit << ", ";
	std::cout << "\n my:";
	for(; mrit != _my.rend(); ++mrit)
		std::cout << *mrit << ", ";
	std::cout << "\n";




	std::cout << "\n\n====== VECTOR - CLEAR TEST ======\n";
	_ori.clear();
	_my.clear();
	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";




	std::cout << "\n\n====== VECTOR - ASSIGN TEST ======\n";
	_ori.assign(100, 42);
	_my.assign(100, 42);
	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";




	std::cout << "\n\n====== VECTOR - RESIZE TEST ======\n";
	_ori.resize(42);
	_my.resize(42);
	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";


	_my.clear();

	ft::vector<int> _my2;
	for(int i = 0; i < 20; ++i)
	{
		_my.push_back(rand() % 50);
		_my2.push_back(rand() % 50);
	}
	std::cout << "\n\n====== VECTOR - SWAP TEST ======\n";
	mit = _my.begin();
	std::cout << " my:";
	for(; mit != _my.end(); ++mit)
		std::cout << *mit << ", ";
	std::cout << "\nmy2:";
	mit = _my2.begin();
	for(; mit != _my2.end(); ++mit)
		std::cout << *mit << ", ";
	std::cout << "\n\n\n";
	_my.swap(_my2);
	mit = _my.begin();
	std::cout << " my:";
	for(; mit != _my.end(); ++mit)
		std::cout << *mit << ", ";
	std::cout << "\nmy2:";
	mit = _my2.begin();
	for(; mit != _my2.end(); ++mit)
		std::cout << *mit << ", ";
	std::cout << "\n\n\n";

}