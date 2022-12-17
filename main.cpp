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


#define TESTED_NAMESPACE ft

# include "map.hpp"

#define _pair TESTED_NAMESPACE::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
	typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}


#include <list>

#define T1 char
#define T2 int
typedef _pair<const T1, T2> T3;

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, (i + 1) * 7));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::iterator it_ = mp.begin();
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator it(it_), ite;
	printSize(mp);

	std::cout << (it_ == it.base()) << std::endl;
	std::cout << (it_ == dec(it, 3).base()) << std::endl;

	printPair(it.base());
	printPair(inc(it.base(), 1));

	std::cout << "TEST OFFSET" << std::endl;
	// printPair(it);
	--it;
	printPair(it);
	printPair(it.base());

	it = mp.rbegin(); ite = mp.rend();
	while (it != ite)
		std::cout << "[rev] " << printPair(it++, false) << std::endl;
	printReverse(mp);

	return (0);
}


// int main()
// {

// 	int seed = 0;
// 	srand(reinterpret_cast<size_t>(&seed));

// 	std::vector<int>	_ori;
// 	ft::vector<int>		_my;



// 	std::cout << "\n\n====== VECTOR - PUSH_BACK TEST ======\n";
// 	int val;
// 	for(int i = 0; i < 40; ++i)
// 	{
// 		val = rand() % 50;
// 		_ori.push_back(val);
// 		_my.push_back(val);
// 	}

// 	std::vector<int>::iterator oit = _ori.begin();
// 	// std::vector<int>::const_iterator coit = _ori.begin();
// 	ft::vector<int>::iterator mit = _my.begin();
// 	// ft::vector<int>::const_iterator cmit = _my.begin();
// 	// std::map<int, int>::iterator mapIt;
// 	// std::map<int, int>::const_iterator cmapIt;
// 	// std::map<int, int> _map;
// 	// ft::map<int, int>::iterator mmapIt;
// 	// ft::map<int, int>::const_iterator mcmapIt;
// 	// ft::map<int, int> _mmap;

// 	// mapIt = _map.begin();
// 	// cmapIt = _map.begin();
// 	// mmapIt = _mmap.begin();
// 	// mcmapIt = _mmap.begin();

// 	// if (mapIt == cmapIt)
// 	// 	std::cout << "Comparable\n";

// 	// if (mmapIt == mcmapIt)
// 	// 	std::cout << "Comparable\n";

// 	// if (oit == coit)
// 	// 	std::cout << "Comparable\n";

// 	// if (mit == cmit)
// 	// 	std::cout << "Comparable\n";




// 	std::cout << "original-";
// 	for(; oit != _ori.end(); ++oit)
// 		std::cout << *oit << ", ";
// 	std::cout << "\n      my-";
// 	for(; mit != _my.end(); ++ mit)
// 		std::cout << *mit << ", ";
// 	std::cout << "\n";
// 	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
// 	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";


// 	std::cout << "\n\n====== VECTOR - POP_BACK TEST ======\n";
// 	for(int i = 0; i < 10; ++i)
// 	{
// 		_ori.pop_back();
// 		_my.pop_back();
// 	}
// 	std::cout << "original-";
// 	oit = _ori.begin();
// 	mit = _my.begin();
// 	for(; oit != _ori.end(); ++oit)
// 		std::cout << *oit << ", ";
// 	std::cout << "\n      my-";
// 	for(; mit != _my.end(); ++ mit)
// 		std::cout << *mit << ", ";
// 	std::cout << "\n";
// 	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
// 	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";



// 	std::cout << "\n\n====== VECTOR - AT TEST ======\n";
// 	for(int i = 5; i < 14; ++i)
// 	{
// 		std::cout << "ori:" << _ori.at(i) << "";
// 		std::cout << " my :" << _my.at(i) << "\n";
// 	}

// 	std::cout << "\n\n====== VECTOR - [] OPERATOR TEST ======\n";
// 	for(int i = 5; i < 14; ++i)
// 	{
// 		std::cout << "ori:" << _ori[i] << "";
// 		std::cout << " my :" << _my[i] << "\n";
// 	}


// 	std::cout << "\n\n====== VECTOR - FRONT TEST ======\n";
// 	std::cout << "ori:" << _ori.front();
// 	std::cout << " my :" << _my.front() << "\n";



// 	std::cout << "\n\n====== VECTOR - BACK TEST ======\n";
// 	std::cout << "ori:" << _ori.back();
// 	std::cout << " my :" << _my.back() << "\n";



// 	std::cout << "\n\n====== VECTOR - DATA TEST ======\n";
// 	int* oriData = _ori.data();
// 	int* myData = _my.data();
// 		std::cout << "ori:";
// 	for(size_t i = 0; i  != _ori.size(); ++i)
// 		std::cout << oriData[i] << ", ";
// 	std::cout << "\n my:";
// 	for(size_t i = 0; i  != _ori.size(); ++i)
// 		std::cout << myData[i] << ", ";
// 	std::cout << "\n";




// 	std::cout << "\n\n====== VECTOR - REVERSE ITERATOR TEST ======\n";
// 	std::vector<int>::reverse_iterator orit = _ori.rbegin();
// 	ft::vector<int>::reverse_iterator mrit = _my.rbegin();

// 	std::cout << "ori:";
// 	for(; orit != _ori.rend(); ++orit)
// 		std::cout << *orit << ", ";
// 	std::cout << "\n my:";
// 	for(; mrit != _my.rend(); ++mrit)
// 		std::cout << *mrit << ", ";
// 	std::cout << "\n";




// 	std::cout << "\n\n====== VECTOR - CLEAR TEST ======\n";
// 	_ori.clear();
// 	_my.clear();
// 	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
// 	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";




// 	std::cout << "\n\n====== VECTOR - ASSIGN TEST ======\n";
// 	_ori.assign(100, 42);
// 	_my.assign(100, 42);
// 	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
// 	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";




// 	std::cout << "\n\n====== VECTOR - RESIZE TEST ======\n";
// 	_ori.resize(42);
// 	_my.resize(42);
// 	std::cout << "ori - size:" << _ori.size() << " capacity:" << _ori.capacity() << "\n";
// 	std::cout << "my  - size:" << _my.size() << " capacity:" << _my.capacity() << "\n";


// 	_my.clear();

// 	ft::vector<int> _my2;
// 	for(int i = 0; i < 20; ++i)
// 	{
// 		_my.push_back(rand() % 50);
// 		_my2.push_back(rand() % 50);
// 	}

// 	std::cout << "\n\n====== VECTOR - SWAP TEST ======\n";
// 	mit = _my.begin();
// 	std::cout << " my:";
// 	for(; mit != _my.end(); ++mit)
// 		std::cout << *mit << ", ";
// 	std::cout << "\nmy2:";
// 	mit = _my2.begin();
// 	for(; mit != _my2.end(); ++mit)
// 		std::cout << *mit << ", ";
// 	std::cout << "\n\n\n";

// 	ft::vector<int>::iterator swapIt = _my.begin();

// 	_my.swap(_my2);
// 	mit = _my.begin();
// 	std::cout << " my:";
// 	for(; mit != _my.end(); ++mit)
// 		std::cout << *mit << ", ";
// 	std::cout << "\nmy2:";
// 	mit = _my2.begin();
// 	for(; mit != _my2.end(); ++mit)
// 		std::cout << *mit << ", ";
// 	std::cout << "\n\n\n";


// 	std::cout << "\n\n====== VECTOR - AFTER SWAP TEST ======\n";
// 	for(; swapIt != _my2.end(); ++swapIt)
// 	{
// 		std::cout  << *swapIt << ", ";
// 	}
// 	std::cout << "\n\n";




// 	std::cout << "\n\n\n\n====== MAP - INSERT TEST ======\n";
// 	std::map<int, int> __ori;
// 	ft::map<int, int> __my;


// 	for(int i = 200; i < 401; ++i)
// 	{
// 		__ori.insert(std::pair<int, int>(i, i));
// 		__my.insert(ft::pair<int, int>(i, i));
// 	}

// 	ft::map<int, int>::iterator insertIt = __my.begin();

// 	for(int i = 1; i < 200; ++i)
// 	{
// 		__ori.insert(std::pair<int, int>(i, i));
// 		__my.insert(ft::pair<int, int>(i, i));
// 	}

// 	std::cout << "\n\n====== MAP - AFTER INSERT, ITERATOR TEST ======\n";
// 	for(; insertIt != __my.end(); ++insertIt)
// 		std::cout << insertIt->first << " ";
// 	std::cout << "\n\n\n\n";

// 	std::map<int, int>::iterator _oit = __ori.begin();
// 	ft::map<int, int>::iterator _mit = __my.begin();

// 	for (; _oit != __ori.end(); ++_oit, ++_mit)
// 	{
// 		if (_oit->first != _mit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_oit == __ori.end() && _mit == __my.end())
// 		std::cout << "OK\n";

// 	--_oit;
// 	--_mit;

// 	for(; _oit != __ori.begin(); --_oit, --_mit)
// 	{
// 		if (_oit->first != _mit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_oit == __ori.begin() && _mit == __my.begin())
// 		std::cout << "OK\n";






// 	std::cout << "\n\n====== MAP - REVERSE ITERATOR TEST ======\n";
// 	std::map<int, int>::reverse_iterator _orit = __ori.rbegin();
// 	ft::map<int, int>::reverse_iterator _mrit = __my.rbegin();

// 	for (; _orit != __ori.rend(); ++_orit, ++_mrit)
// 	{
// 		if (_orit->first != _mrit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_orit == __ori.rend() && _mrit == __my.rend())
// 		std::cout << "OK\n";

// 	--_orit;
// 	--_mrit;

// 	for(; _orit != __ori.rbegin(); --_orit, --_mrit)
// 	{
// 		if (_orit->first != _mrit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_orit == __ori.rbegin() && _mrit == __my.rbegin())
// 		std::cout << "OK\n";




// 	std::cout << "\n\n====== MAP - CLEAR TEST ======\n";
// 	std::cout << "ori size:" << __ori.size();
// 	std::cout << "\n my size:" << __my.size();
// 	__ori.clear();
// 	__my.clear();
// 	std::cout << "\n\nAFTER CLEAR\n";
// 	std::cout << "ori size:" << __ori.size();
// 	std::cout << "\n my size:" << __my.size();

// 	std::cout << "\n\n====== MAP - EMPTY TEST ======\n";
// 	std::cout << std::boolalpha;
// 	std::cout << __ori.empty();
// 	std::cout << "\n" << __my.empty() << "\n";




// 	for(int i = 1; i < 401; ++i)
// 	{
// 		__ori.insert(std::pair<int, int>(i, i));
// 		__my.insert(ft::pair<int, int>(i, i));
// 	}

// 	_oit = __ori.begin();
// 	_mit = __my.begin();
// 	std::cout << "\n\n====== MAP - ERASE TEST ======\n";

// 	__ori.erase(42);
// 	__my.erase(42);

	
// 	for(; _oit != __ori.end(); ++_oit, ++_mit)
// 	{
// 		if (_oit->first != _mit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_oit == __ori.end() && _mit == __my.end())
// 		std::cout << "OK\n";



// 	_oit = __ori.begin();
// 	_mit = __my.begin();

// 	for(int i = 0; i < 340; ++i)
// 	{
// 		++_oit;
// 		++_mit;
// 	}


// 	__ori.erase(_oit);
// 	__my.erase(_mit);


// 	_oit = __ori.begin();
// 	_mit = __my.begin();
// 	for(; _oit != __ori.end(); ++_oit, ++_mit)
// 	{
// 		if (_oit->first != _mit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_oit == __ori.end() && _mit == __my.end())
// 		std::cout << "OK\n";



// 	_oit = __ori.begin();
// 	_mit = __my.begin();

// 	for(int i = 0; i < 300; ++i)
// 	{
// 		++_oit;
// 		++_mit;
// 	}

// 	__ori.erase(__ori.begin(), _oit);
// 	__my.erase(__my.begin(), _mit);


// 	_oit = __ori.begin();
// 	_mit = __my.begin();
// 	insertIt = __my.begin();
// 	for(; _oit != __ori.end(); ++_oit, ++_mit)
// 	{
// 		if (_oit->first != _mit->first)
// 			std::cout << "THIS MESSAGE WILL BE PRINTED WEHN FAILED TEST\n";
// 	}
// 	if (_oit == __ori.end() && _mit == __my.end())
// 		std::cout << "OK\n\n\n";


// 	std::cout << "====== AFTER ERASE, ITERATOR STILL WORK ======\n";
// 	for(; insertIt != __my.end(); ++insertIt)
// 		std::cout << insertIt->first << " ";
// 	if (insertIt == __my.end())
// 		std::cout << "\n\nOK\n";
// 	std::cout << "\n\n\n\n";




// 	std::cout << "\n\n====== MAP - SWAP TEST ======\n";
// 	ft::map<int, int> __my2;
// 	for(int i = 0; i < 42; ++i)
// 	{
// 		__my2.insert(ft::pair<int, int>(i, i));
// 	}

// 	_mit = __my.begin();
// 	for(; _mit != __my.end(); ++_mit)
// 	{
// 		std::cout << _mit->first << " ";
// 	}
// 	std::cout << "\n\n";

// 	_mit = __my2.begin();
// 	for(; _mit != __my2.end(); ++_mit)
// 	{
// 		std::cout << _mit->first << " ";
// 	}


// 	ft::map<int, int>::iterator mapSwapIt = __my.begin();
// 	for (int i = 0; i < 5; ++i)
// 		++mapSwapIt;


// 	std::cout << "\n";
// 	__my.swap(__my2);

// 	std::cout << "\n====== AFTER SWAP ======\n";
// 	_mit = __my.begin();
// 	for(; _mit != __my.end(); ++_mit)
// 	{
// 		std::cout << _mit->first << " ";
// 	}
// 	std::cout << "\n\n";

// 	_mit = __my2.begin();
// 	for(; _mit != __my2.end(); ++_mit)
// 	{
// 		std::cout << _mit->first << " ";
// 	}



// 	std::cout << "\n\n\n\n====== MAP - AFTER SWAP ITERATOR TEST ======\n";
// 	for(; mapSwapIt != __my2.end(); ++mapSwapIt)
// 		std::cout << mapSwapIt->first << " ";
// 	std::cout << "\n\n\n";










// 	std::cout << "\n\n====== MAP - FIND TEST ======\n";
// 	for(int i = 0; i < 10; ++i)
// 	{
// 		val = rand() % 400;
// 		std::cout << "find key:" << val << "\n";
// 		if (val == __ori.find(val)->first && val == __my2.find(val)->first)
// 		{
// 			std::cout << "ori:exist\n";
// 			std::cout << " my:exist\n";
// 		}
// 		else
// 		{
// 			std::cout << "ori:not exist\n";
// 			std::cout << "my :not exist\n";
// 		}
// 		std::cout << "-----------------------------------\n";
// 	}








// 	std::cout << "\n\n\n\n====== STACK - TEST ======\n";
// 	std::stack<int> ___ori;
// 	ft::stack<int> ___my;



// 	for(int i = 0; i < 20; ++i)
// 	{
// 		val = rand() % 50;
// 		___ori.push(val);
// 		___my.push(val);
// 	}

// 	std::cout << "ori size:" << ___ori.size() << "\n";
// 	std::cout << " my size:" << ___my.size() << "\n";
// 	std::cout << "ori empty:" << ___ori.empty() << "\n";
// 	std::cout << " my empty:" << ___my.empty() << "\n";
// 	std::cout << "\n\n";
// 	std::cout << "ori top:" << ___ori.top();
// 	std::cout << "\n my top:" << ___my.top() << "\n";
// 	std::cout << "================================================\n\n";

// 	for(int i = 0; i < 19; ++i)
// 	{
// 		___ori.pop();
// 		___my.pop();
// 		std::cout << "ori top:" << ___ori.top() << "\n";
// 		std::cout << " my top:" << ___my.top() << "\n";
// 		std::cout << "----------------------------------\n";
// 	}
// 	___ori.pop();
// 	___my.pop();

// 	std::cout << "ori size:" << ___ori.size() << "\n";
// 	std::cout << " my size:" << ___my.size() << "\n";
// 	std::cout << "ori empty:" << ___ori.empty() << "\n";
// 	std::cout << " my empty:" << ___my.empty() << "\n";

// 	return 0;
// }



// template <class T, class Alloc>
// void	cmp(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	static int i = 0;

// 	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
// 	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
// 	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
// 	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
// }

// int		main(void)
// {
// 	ft::vector<int> vct(4);
// 	ft::vector<int> vct2(4);

// 	cmp(vct, vct);  // 0
// 	cmp(vct, vct2); // 1

// 	vct2.resize(10);

// 	cmp(vct, vct2); // 2
// 	cmp(vct2, vct); // 3

// 	vct[2] = 42;

// 	cmp(vct, vct2); // 4
// 	cmp(vct2, vct); // 5

// 	swap(vct, vct2);

// 	cmp(vct, vct2); // 6
// 	cmp(vct2, vct); // 7

// 	return (0);
// }


// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_two(4);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_three;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_four;

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = (vct.size() - i) * 3;
// 	for (unsigned long int i = 0; i < vct_two.size(); ++i)
// 		vct_two[i] = (vct_two.size() - i) * 5;
// 	printSize(vct);
// 	printSize(vct_two);

// 	vct_three.assign(vct.begin(), vct.end());
// 	vct.assign(vct_two.begin(), vct_two.end());
// 	vct_two.assign(2, 42);
// 	vct_four.assign(4, 21);

// 	std::cout << "\t### After assign(): ###" << std::endl;

// 	printSize(vct);
// 	printSize(vct_two);
// 	printSize(vct_three);
// 	printSize(vct_four);

// 	vct_four.assign(6, 84);
// 	printSize(vct_four);

// 	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

// 	vct.assign(5, 53);
// 	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

// 	printSize(vct);
// 	printSize(vct_two);

// 	return (0);
// }



// void	is_empty(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct)
// {
// 	std::cout << "is_empty: " << vct.empty() << std::endl;
// }

// int		main(void)
// {
// 	const int start_size = 7;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(start_size, 20);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

// 	for (int i = 2; i < start_size; ++i)
// 		it[i] = (start_size - i) * 3;
// 	printSize(vct, true);

// 	vct.resize(10, 42);
// 	printSize(vct, true);

// 	vct.resize(18, 43);
// 	printSize(vct, true);
// 	vct.resize(10);
// 	printSize(vct, true);
// 	vct.resize(23, 44);
// 	printSize(vct, true);
// 	vct.resize(5);
// 	printSize(vct, true);
// 	vct.reserve(5);
// 	vct.reserve(3);
// 	printSize(vct, true);
// 	vct.resize(87);
// 	vct.resize(5);
// 	printSize(vct, true);

// 	is_empty(vct2);
// 	vct2 = vct;
// 	is_empty(vct2);
// 	vct.reserve(vct.capacity() + 1);
// 	printSize(vct, true);
// 	printSize(vct2, true);

// 	vct2.resize(0);
// 	is_empty(vct2);
// 	printSize(vct2, true);
// 	return (0);
// }





// int		main(void)
// {
// 	const int size = 5;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_ = vct.begin();
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it(it_);

// 	for (int i = 0; i < size; ++i)
// 		vct[i] = (i + 1) * 5;
// 	printSize(vct);

	// std::cout << (it_ == it.base()) << std::endl;
	// std::cout << (it_ == (it + 3).base()) << std::endl;

	// std::cout << *(it.base() + 1) << std::endl;
	// std::cout << *(it - 3) << std::endl;
	// std::cout << *(it - 3) << std::endl;
	// std::cout << *(it - 3).base() << std::endl;
	// it -= 3;
	// std::cout << *it.base() << std::endl;

	// std::cout << "TEST OFFSET" << std::endl;
	// std::cout << *(it) << std::endl;
	// std::cout << *(it).base() << std::endl;
	// std::cout << *(it - 0) << std::endl;
	// std::cout << *(it - 0).base() << std::endl;
	// std::cout << *(it - 1).base() << std::endl;

// 	return (0);
// }


// #define TESTED_TYPE int

// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit = vct.begin();

// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit(it);

// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit(rit);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_(it);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_2(cit);

// 	/* error expected
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit_(crit);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit2(cit);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it2(rit);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit2(crit);
// 	*/

// 	std::cout << "OK" << std::endl;
// 	return (0);
// }


// #define TESTED_TYPE std::string

// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(8);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		it[i] = std::string((vct.size() - i), i + 65);
// 	printSize(vct, true);

// 	std::cout << "push_back():\n" << std::endl;

// 	vct.push_back("One long string");
// 	vct2.push_back("Another long string");

// 	printSize(vct);
// 	printSize(vct2);

// 	vct.pop_back();
// 	vct2.pop_back();

// 	printSize(vct);
// 	printSize(vct2);

// 	return (0);
// }

// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(5);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
// 	const int cut = 3;

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = (vct.size() - i) * 7;
// 	printSize(vct);

// 	vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
// 	printSize(vct2);
// 	vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
// 	printSize(vct2);
// 	vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);
// 	printSize(vct2);

// 	std::cout << "insert return:" << std::endl;

// 	std::cout << *vct2.insert(vct2.end(), 42) << std::endl;
// 	std::cout << *vct2.insert(vct2.begin() + 5, 84) << std::endl;
// 	std::cout << "----------------------------------------" << std::endl;

// 	printSize(vct2);
// 	return (0);
// }


// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct3;

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = (vct.size() - i) * 3;
// 	printSize(vct);

// 	vct2.insert(vct2.end(), 42);
// 	vct2.insert(vct2.begin(), 2, 21);
// 	printSize(vct2);

// 	vct2.insert(vct2.end() - 2, 42);
// 	printSize(vct2);

// 	vct2.insert(vct2.end(), 2, 84);
// 	printSize(vct2);

// 	vct2.resize(4);
// 	printSize(vct2);

// 	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
// 	vct.clear();
// 	printSize(vct2);

// 	printSize(vct);

// 	for (int i = 0; i < 5; ++i)
// 		vct3.insert(vct3.end(), i);
// 	vct3.insert(vct3.begin() + 1, 2, 111);
// 	printSize(vct3);

// 	return (0);
// }


// int		main(void)
// {
// 	std::list<TESTED_TYPE> lst;
// 	std::list<TESTED_TYPE>::iterator lst_it;
// 	for (int i = 1; i < 5; ++i)
// 		lst.push_back(i * 3);

// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
// 	printSize(vct);

// 	lst_it = lst.begin();
// 	for (int i = 1; lst_it != lst.end(); ++i)
// 		*lst_it++ = i * 5;
// 	vct.assign(lst.begin(), lst.end());
// 	printSize(vct);

// 	vct.insert(vct.end(), lst.rbegin(), lst.rend());
// 	printSize(vct);
// 	return (0);
// }

// #define TESTED_TYPE std::string

// void	checkErase(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct,
// 					TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator const &it)
// {
// 	static int i = 0;
// 	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
// 	printSize(vct);
// }

// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = std::string((vct.size() - i), i + 65);
// 	printSize(vct);

// 	checkErase(vct, vct.erase(vct.begin() + 2));

// 	checkErase(vct, vct.erase(vct.begin()));
// 	checkErase(vct, vct.erase(vct.end() - 1));

// 	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
// 	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

// 	vct.push_back("Hello");
// 	vct.push_back("Hi there");
// 	printSize(vct);
// 	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

// 	vct.push_back("ONE");
// 	vct.push_back("TWO");
// 	vct.push_back("THREE");
// 	vct.push_back("FOUR");
// 	printSize(vct);
// 	checkErase(vct, vct.erase(vct.begin(), vct.end()));

// 	return (0);
// }

