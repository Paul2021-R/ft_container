/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:20 by seojin            #+#    #+#             */
/*   Updated: 2022/12/05 20:33:58 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>		// for std::allocator
#include <stdexcept>	// for std::out_of_range, std::length_error
#include <limits>		// for std::numeric_limits
#include "vector_iterator.hpp"
#include "utility.hpp"

namespace ft
{

template < class T, class Allocator = std::allocator<T> >
class vector
{
public:
	typedef T														value_type;
	typedef Allocator												allocator_type;
	typedef	typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::size_type						size_type;
	typedef typename allocator_type::difference_type				difference_type;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename ft::vector_iterator<value_type>				iterator;
	typedef typename ft::vector_iterator<const value_type>			const_iterator;
	typedef typename ft::reverse_vector_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_vector_iterator<const_iterator>	const_reverse_iterator;






	/* ====== Constructors & Desctructor ====== */
	explicit vector( const allocator_type& alloc = allocator_type()) :
				_allocator(alloc), _vector(NULL), _size(0), _capacity(0) {}
	explicit vector( size_type cnt, const T& value = T(), const Allocator& alloc = Allocator()) :
				_allocator(alloc), _vector(NULL), _size(cnt), _capacity(cnt)
	{
		_vector = _allocator.allocate(cnt);
		if (value)
		{
			for(size_type i = 0; i < _size; ++i)
				_allocator.construct(&_vector[i], value);
		}
	}
	template < class InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL) :
			_allocator(alloc), _vector(NULL), _size(0), _capacity(0)
	{
		if (first <= last)
		{
			size_t size = 0;
			InputIt tmp = first;
			while (tmp != last)
			{
				++tmp;
				++size;
			}

			_vector = _allocator.allocate(size);
			_size = size;
			_capacity = size;

			for(int i = 0; first != last; ++first, ++i)
				_allocator.construct(&_vector[i], *first);
		}
	}
	vector( const vector& other ) :
			_allocator(other._allocator), _vector(NULL), _size(other._size), _capacity(other._capacity)
	{
		_vector = _allocator.allocate(_capacity);
		const_iterator it = other.begin();
		for(size_type i = 0; it != other.end(); ++it, ++i)
			_allocator.construct(&_vector[i], *it);
	}
	~vector()
	{
		for(iterator it = begin(); it != end(); ++it)
			_allocator.destroy(it.operator->());
		_allocator.deallocate(_vector, _capacity);
	}


	/* ====== Copy Assignment ====== */
	vector operator=( const vector& other )
	{
		if (_capacity)
		{
			for(iterator it = begin(); it != end(); ++it)
				_allocator.destroy(it.operator->());
			_allocator.deallocate(_vector, _capacity);
		}

		_allocator = other._allocator;
		_size = other._size;
		_capacity = other._capacity;
		_vector = _allocator.allocate(_capacity);
		const_iterator it = other.begin();
		for (size_type i = 0; it != other.end(); ++it, ++i)
			_allocator.construct(&_vector[i], *it);

		return *this;
	}



	/* ====== Assign ====== */
	void assign( size_type cnt, const_reference value )
	{
		if (_capacity < cnt)
			*this = vector(cnt, value);
		else
		{
			for (iterator it = begin(); it != end(); ++it)
				_allocator.destroy(it.operator->());

			for (size_type i = 0; i < cnt; ++i)
				_allocator.construct(&_vector[i], value);
			_size = cnt;
		}
	}

	template <class InputIt>
	void assign( InputIt first, InputIt last )
	{
		size_type cnt = 0;
		InputIt it = first;
		while (it != last)
		{
			++cnt;
			++it;
		}

		if (_capacity < cnt)
			*this = vector(first, last);
		else
		{
			it = begin();
			for(; it != end(); ++it)
				_allocator.destroy(it.operator->());
			
			for (int i = 0; first != last; ++first, ++i)
				_allocator.construct(&_vector[i], *first);
		}
	}


	/* ====== get_allocator ====== */
	allocator_type get_allocator( void ) const { return std::allocator<T>(); }




	/* ====== Element Access ====== */
	reference at( size_type pos )
	{
		if(_size <= pos)
			throw std::out_of_range("Error: ft::vector<T, Alloc> - at, OUT OF RANGE ERR");
		return *(_vector + pos);
	}

	const_reference at( size_type pos ) const
	{
		if (_size <= pos)
			throw std::out_of_range("Error: ft::vector<T, Alloc> - at, OUT OF RANGE ERR");
		return *(_vector + pos);
	}

	reference operator[]( size_type pos ) { return *(_vector + pos); }
	const_reference operator[]( size_type pos ) const { return *(_vector + pos); }

	reference front( void ) { return *_vector; }
	const_reference front( void ) const { return *_vector; }

	reference back( void ) { return *(_vector + _size - 1); }
	const_reference back( void ) const { return *(_vector + _size - 1); }

	pointer data( void ) { return _vector; }
	const_pointer data( void ) const { return _vector; }







	/* ====== Iterators ====== */
	const_iterator	begin( void ) const { return const_iterator(_vector); }
	iterator		begin( void ) { return iterator(_vector); }
	const_iterator	end( void ) const { return const_iterator(_vector + _size); }
	iterator		end( void ) { return iterator(_vector + _size); }
	
	const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(_vector + _size - 1); }
	reverse_iterator		rbegin( void ) { return reverse_iterator(_vector + _size - 1); }
	const_reverse_iterator	rend( void ) const { return const_reverse_iterator(_vector - 1); }
	reverse_iterator		rend( void ) { return reverse_iterator(_vector - 1); }







	/* ====== Capacity ====== */
	bool empty( void ) const { return _size == 0; }
	size_type max_size( void ) const { return _allocator.max_size(); }
	size_type size( void ) const { return _size; }
	size_type capacity( void ) const { return _capacity; }
	void reserve( size_type new_cap )
	{
		if ( new_cap > max_size())
			throw std::length_error("Error: ft::vector<T, Alloc> - reverse, LENGTH ERR");
		if ( new_cap > _capacity )
		{
			vector tmp(new_cap);
			iterator it = begin();
			int i = 0;
			for (; it != end(); ++it, ++i)
				tmp._allocator.construct(&tmp._vector[i], *it);
			tmp._size = i;
			*this = tmp;
		}
	}
	void clear( void )
	{
		iterator it = begin();
		for(; it != end(); ++it)
			_allocator.destroy(it.operator->());
		_size = 0;
	}



	/* ====== Modifiers ====== */
	iterator insert( const_iterator pos, const_reference value )
	{
		if ( pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		difference_type diff = pos - begin();

		if (_size == _capacity)
			_capacity *= 2;
		vector tmp(_capacity);

		size_type i = 0;
		const_iterator it = begin();
		while (it != pos)
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}
		
		tmp._allocator.construct(&tmp._vector[i], value);
		++i;

		while (it != end())
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}
		tmp._size = i;
		*this = tmp;
		return (_vector + diff);
	}
	void insert( const_iterator pos, size_type count, const_reference value )
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");


		difference_type diff = pos - begin();
		while (_capacity < _size + count)
			_capacity *= 2;
		
		vector tmp(_capacity);
		const_iterator it = begin();
		size_type i = 0;
		while (it != pos)
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}

		while (count)
		{
			tmp._allocator.construct(&tmp._vector[i], value);
			++i;
			--count;
		}

		while (it != end())
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}
		tmp._size = i;
		*this = tmp;
	}
	template <class InputIt>
	void insert( const_iterator pos, InputIt first, InputIt last )
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		if (first > last)
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");
		
		difference_type diff = pos - begin();
		while (_capacity < _size + last - first)
			_capacity *= 2;
		
		vector tmp(_capacity);

		size_t i = 0;
		const_iterator it = begin();
		while (it != pos)
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}

		while (first != last)
		{
			tmp._allocator.construct(&tmp._vector[i], *first);
			++first;
			++i;
		}

		while (it != end())
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}

		tmp._size = i;
		*this = tmp;
	}

	iterator erase( iterator pos )
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - erase, OUT OF RANGE ERR");

		vector tmp(_capacity);
		difference_type diff = pos - begin();
		size_t i = 0;
		iterator it = begin();
		while (it != pos)
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}
		++it;
		while (it != end())
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}
		*this = tmp;
		return (iterator(_vector + diff));
	}
	iterator erase( iterator first, iterator last )
	{

		if (first < begin() || last > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		if (first > last)
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		difference_type diff = last - begin();

		vector tmp(_capacity);
		iterator it = begin();
		size_t i = 0;
		
		while (it != first)
		{
			tmp._allocator.construct(&tmp._vector[i], *it);
			++it;
			++i;
		}

		while (it != last)
			++it;

		for(; it != end(); ++it, ++i)
			tmp._allocator.construct(&tmp._vector[i], *it);
		
		tmp._size = i;
		*this = tmp;

		return iterator(_vector + diff);
	}

	void push_back( const_reference value )
	{
		if (_size == _capacity)
		{
			_capacity ? _capacity *= 2 : _capacity = 1;

			vector tmp(_capacity);
			size_t i = 0;
			iterator it = begin();
			for(; it != end(); ++it, ++i)
				tmp._allocator.construct(&tmp._vector[i], *it);
			tmp._allocator.construct(&tmp._vector[i], value);
			++i;
			tmp._size = i;
			*this = tmp;
		}
		else
		{
			_allocator.construct(&_vector[_size], value);
			_size++;
		}
	}

	void pop_back( void )
	{
		if (_size)
		{
			_allocator.destroy((end() - 1).operator->());
			--_size;
		}
	}
	void resize( size_type n, value_type value = value_type() )
	{
		if (n < 0)
			throw std::out_of_range("Error: ft::vector<T, Alloc> - reverse, LENGTH ERR");
		if (n < _capacity)
		{
			iterator it = begin();
			int i = 0;
			for(; it != end() && i < n; ++it, ++i);

			while (it != end())
			{
				_allocator.destroy(it.operator->());
				++it;
			}

			while (i < n)
			{
				_allocator.construct(&_vector[i], value);
				++i;
			}
			_size = n;
		}
		else
		{
			while (_capacity < n)
				_capacity *= 2;

			vector tmp(_capacity);
			iterator it = begin();
			size_t i = 0;
			for(; it != end(); ++it, ++it)
				tmp._allocator.construct(&tmp._vector[i], *it);
			for(; i < n; ++i)
				tmp._allocator.construct(&tmp._vector[i], value);

			tmp._size = n;
			*this = tmp;
		}
	}
	void swap ( vector& other )
	{
		vector tmp(other);

		other = *this;
		*this = tmp;
	}


private:
	allocator_type	_allocator; 
	pointer			_vector;
	size_type		_size;
	size_type		_capacity;
};




/* ====== Operator Overloading & Non member functions ====== 
Opearators are `Non - Member functions` so, implement outside of vector class
lhs == "left hand side", hrs == "right hand side" */


template <class T, class Alloc>
void swap( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs )
{
	vector<T, Alloc> tmp(lhs);

	lhs = rhs;
	rhs = tmp;
}

template <class T, class Alloc>
bool operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) { return lhs == rhs; }

template <class T, class Alloc>
bool operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) { return lhs != rhs; }

template <class T, class Alloc>
bool operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) { return lhs > rhs; }

template <class T, class Alloc>
bool operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) { return lhs < rhs; }

template <class T, class Alloc>
bool operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) { return lhs >= rhs; }

template <class T, class Alloc>
bool operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) { return lhs <= rhs; }




}