#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>

// #define MAX_RAM 42949672
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	std::cout << "here\n";
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}

// #include <stdexcept>
// #include <vector>
// #include <iostream>
// #include <iterator>
// #include "vector.hpp"
// #include <memory>
// #include <typeinfo>
// #include <type_traits>
// #include "utility.hpp"
// #include <map>
// #include <utility>
// #include <stdlib.h>
// #include "map.hpp"
// #include <stack>
// #include "stack.hpp"
// int main()
// {
// 	ft::map<int, int> _map;
// 	for(int i = 0; i < 50; ++i)
// 	{
// 		_map.insert(ft::pair<int, int>(i, 100 - i));
// 	}

// 	ft::map<int, int>::reverse_iterator it = _map.rbegin();
// 	for(; it != _map.rend(); ++it)
// 		std::cout << it->first << ":" << it->second << "\n";

	// ft::map<int, int>::reverse_iterator rit = _map.rbegin();


	// ft::vector<int> _vec;
	// for(int i = 0; i < 100; ++i)
	// {
	// 	_vec.push_back(i);
	// }
	// ft::vector<int>::reverse_iterator rit = _vec.rbegin();


	/* ============= map - equal_range test ============= */
	// ft::map<int, const char *> m;

	// m.insert(ft::pair<int, const char *>(0, "zero"));
	// m.insert(ft::pair<int, const char *>(1, "one"));
	// m.insert(ft::pair<int, const char *>(2, "two"));

	
	// ft::pair<ft::map<int, const char *>::iterator, ft::map<int, const char *>::iterator> p = m.equal_range(1);
	// for (ft::map<int, const char *>::iterator q = p.first; q != p.second; ++q)
	// {
	// 	std::cout << "m[" << q->first << "] = " << q->second << '\n';
	// }

	// if (p.second == m.find(2))
	// {
	// 	std::cout << "end of equal_range (p.second) is one-past p.first\n";
	// }
	// else
	// {
	// 	std::cout << "unexpected; p.second expected to be one-past p.first\n";
	// }
	

	// {
	// 	ft::pair<ft::map<int, const char *>::iterator, ft::map<int, const char *>::iterator> pp = m.equal_range(-1);
	// 	if (pp.first == m.begin())
	// 	{
	// 		std::cout << "pp.first is iterator to first not-less than -1\n";
	// 	}
	// 	else
	// 	{
	// 		std::cout << "unexpected pp.first\n";
	// 	}

	// 	if (pp.second == m.begin())
	// 	{
	// 		std::cout << "pp.second is iterator to first element greater-than -1\n";
	// 	}
	// 	else
	// 	{
	// 		std::cout << "unexpected pp.second\n";
	// 	}
	// }

	// {
	// 	ft::pair<ft::map<int, const char *>::iterator, ft::map<int, const char *>::iterator> ppp = m.equal_range(3);
	// 	if (ppp.first == m.end())
	// 	{
	// 		std::cout << "ppp.first is iterator to first not-less than 3\n";
	// 	}
	// 	else
	// 	{
	// 		std::cout << "unexpected ppp.first\n";
	// 	}

	// 	if (ppp.second == m.end())
	// 	{
	// 		std::cout << "ppp.second is iterator to first element greater-than 3\n";
	// 	}
	// 	else
	// 	{
	// 		std::cout << "unexpected ppp.second\n";
	// 	}
	// }
// }