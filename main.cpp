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
	int val;
	for(int i = 0; i < 40; ++i)
	{
		val = rand() % 50;
		_ori.push_back(val);
		_my.push_back(val);
	}

	std::vector<int>::iterator oit = _ori.begin();
	// std::vector<int>::const_iterator coit = _ori.begin();
	ft::vector<int>::iterator mit = _my.begin();
	// ft::vector<int>::const_iterator cmit = _my.begin();
	// std::map<int, int>::iterator mapIt;
	// std::map<int, int>::const_iterator cmapIt;
	// std::map<int, int> _map;
	// ft::map<int, int>::iterator mmapIt;
	// ft::map<int, int>::const_iterator mcmapIt;
	// ft::map<int, int> _mmap;

	// mapIt = _map.begin();
	// cmapIt = _map.begin();
	// mmapIt = _mmap.begin();
	// mcmapIt = _mmap.begin();

	// if (mapIt == cmapIt)
	// 	std::cout << "Comparable\n";

	// if (mmapIt == mcmapIt)
	// 	std::cout << "Comparable\n";

	// if (oit == coit)
	// 	std::cout << "Comparable\n";

	// if (mit == cmit)
	// 	std::cout << "Comparable\n";




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

	ft::vector<int>::iterator swapIt = _my.begin();

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


	std::cout << "\n\n====== VECTOR - AFTER SWAP TEST ======\n";
	for(; swapIt != _my2.end(); ++swapIt)
	{
		std::cout  << *swapIt << ", ";
	}
	std::cout << "\n\n";




	std::cout << "\n\n\n\n====== MAP - INSERT TEST ======\n";
	std::map<int, int> __ori;
	ft::map<int, int> __my;


	for(int i = 200; i < 401; ++i)
	{
		__ori.insert(std::pair<int, int>(i, i));
		__my.insert(ft::pair<int, int>(i, i));
	}

	ft::map<int, int>::iterator insertIt = __my.begin();

	for(int i = 1; i < 200; ++i)
	{
		__ori.insert(std::pair<int, int>(i, i));
		__my.insert(ft::pair<int, int>(i, i));
	}

	std::cout << "\n\n====== MAP - AFTER INSERT, ITERATOR TEST ======\n";
	for(; insertIt != __my.end(); ++insertIt)
		std::cout << insertIt->first << " ";
	std::cout << "\n\n\n\n";

	std::map<int, int>::iterator _oit = __ori.begin();
	ft::map<int, int>::iterator _mit = __my.begin();

	for (; _oit != __ori.end(); ++_oit, ++_mit)
	{
		if (_oit->first != _mit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_oit == __ori.end() && _mit == __my.end())
		std::cout << "OK\n";

	--_oit;
	--_mit;

	for(; _oit != __ori.begin(); --_oit, --_mit)
	{
		if (_oit->first != _mit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_oit == __ori.begin() && _mit == __my.begin())
		std::cout << "OK\n";






	std::cout << "\n\n====== MAP - REVERSE ITERATOR TEST ======\n";
	std::map<int, int>::reverse_iterator _orit = __ori.rbegin();
	ft::map<int, int>::reverse_iterator _mrit = __my.rbegin();

	for (; _orit != __ori.rend(); ++_orit, ++_mrit)
	{
		if (_orit->first != _mrit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_orit == __ori.rend() && _mrit == __my.rend())
		std::cout << "OK\n";

	--_orit;
	--_mrit;

	for(; _orit != __ori.rbegin(); --_orit, --_mrit)
	{
		if (_orit->first != _mrit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_orit == __ori.rbegin() && _mrit == __my.rbegin())
		std::cout << "OK\n";




	std::cout << "\n\n====== MAP - CLEAR TEST ======\n";
	std::cout << "ori size:" << __ori.size();
	std::cout << "\n my size:" << __my.size();
	__ori.clear();
	__my.clear();
	std::cout << "\n\nAFTER CLEAR\n";
	std::cout << "ori size:" << __ori.size();
	std::cout << "\n my size:" << __my.size();

	std::cout << "\n\n====== MAP - EMPTY TEST ======\n";
	std::cout << std::boolalpha;
	std::cout << __ori.empty();
	std::cout << "\n" << __my.empty() << "\n";




	for(int i = 1; i < 401; ++i)
	{
		__ori.insert(std::pair<int, int>(i, i));
		__my.insert(ft::pair<int, int>(i, i));
	}

	_oit = __ori.begin();
	_mit = __my.begin();
	std::cout << "\n\n====== MAP - ERASE TEST ======\n";

	__ori.erase(42);
	__my.erase(42);

	
	for(; _oit != __ori.end(); ++_oit, ++_mit)
	{
		if (_oit->first != _mit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_oit == __ori.end() && _mit == __my.end())
		std::cout << "OK\n";



	_oit = __ori.begin();
	_mit = __my.begin();

	for(int i = 0; i < 340; ++i)
	{
		++_oit;
		++_mit;
	}


	__ori.erase(_oit);
	__my.erase(_mit);


	_oit = __ori.begin();
	_mit = __my.begin();
	for(; _oit != __ori.end(); ++_oit, ++_mit)
	{
		if (_oit->first != _mit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_oit == __ori.end() && _mit == __my.end())
		std::cout << "OK\n";



	_oit = __ori.begin();
	_mit = __my.begin();

	for(int i = 0; i < 300; ++i)
	{
		++_oit;
		++_mit;
	}

	__ori.erase(__ori.begin(), _oit);
	__my.erase(__my.begin(), _mit);


	_oit = __ori.begin();
	_mit = __my.begin();
	insertIt = __my.begin();
	for(; _oit != __ori.end(); ++_oit, ++_mit)
	{
		if (_oit->first != _mit->first)
			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
	}
	if (_oit == __ori.end() && _mit == __my.end())
		std::cout << "OK\n\n\n";


	std::cout << "====== AFTER ERASE, ITERATOR STILL WORK ======\n";
	for(; insertIt != __my.end(); ++insertIt)
		std::cout << insertIt->first << " ";
	if (insertIt == __my.end())
		std::cout << "\n\nOK\n";
	std::cout << "\n\n\n\n";




	std::cout << "\n\n====== MAP - SWAP TEST ======\n";
	ft::map<int, int> __my2;
	for(int i = 0; i < 42; ++i)
	{
		__my2.insert(ft::pair<int, int>(i, i));
	}

	_mit = __my.begin();
	for(; _mit != __my.end(); ++_mit)
	{
		std::cout << _mit->first << " ";
	}
	std::cout << "\n\n";

	_mit = __my2.begin();
	for(; _mit != __my2.end(); ++_mit)
	{
		std::cout << _mit->first << " ";
	}


	ft::map<int, int>::iterator mapSwapIt = __my.begin();
	for (int i = 0; i < 5; ++i)
		++mapSwapIt;


	std::cout << "\n";
	__my.swap(__my2);

	std::cout << "\n====== AFTER SWAP ======\n";
	_mit = __my.begin();
	for(; _mit != __my.end(); ++_mit)
	{
		std::cout << _mit->first << " ";
	}
	std::cout << "\n\n";

	_mit = __my2.begin();
	for(; _mit != __my2.end(); ++_mit)
	{
		std::cout << _mit->first << " ";
	}



	std::cout << "\n\n\n\n====== MAP - AFTER SWAP ITERATOR TEST ======\n";
	for(; mapSwapIt != __my2.end(); ++mapSwapIt)
		std::cout << mapSwapIt->first << " ";
	std::cout << "\n\n\n";










	std::cout << "\n\n====== MAP - FIND TEST ======\n";
	for(int i = 0; i < 10; ++i)
	{
		val = rand() % 400;
		std::cout << "find key:" << val << "\n";
		if (val == __ori.find(val)->first && val == __my2.find(val)->first)
		{
			std::cout << "ori:exist\n";
			std::cout << " my:exist\n";
		}
		else
		{
			std::cout << "ori:not exist\n";
			std::cout << "my :not exist\n";
		}
		std::cout << "-----------------------------------\n";
	}








	std::cout << "\n\n\n\n====== STACK - TEST ======\n";
	std::stack<int> ___ori;
	ft::stack<int> ___my;



	for(int i = 0; i < 20; ++i)
	{
		val = rand() % 50;
		___ori.push(val);
		___my.push(val);
	}

	std::cout << "ori size:" << ___ori.size() << "\n";
	std::cout << " my size:" << ___my.size() << "\n";
	std::cout << "ori empty:" << ___ori.empty() << "\n";
	std::cout << " my empty:" << ___my.empty() << "\n";
	std::cout << "\n\n";
	std::cout << "ori top:" << ___ori.top();
	std::cout << "\n my top:" << ___my.top() << "\n";
	std::cout << "================================================\n\n";

	for(int i = 0; i < 19; ++i)
	{
		___ori.pop();
		___my.pop();
		std::cout << "ori top:" << ___ori.top() << "\n";
		std::cout << " my top:" << ___my.top() << "\n";
		std::cout << "----------------------------------\n";
	}
	___ori.pop();
	___my.pop();

	std::cout << "ori size:" << ___ori.size() << "\n";
	std::cout << " my size:" << ___my.size() << "\n";
	std::cout << "ori empty:" << ___ori.empty() << "\n";
	std::cout << " my empty:" << ___my.empty() << "\n";

	return 0;
}



