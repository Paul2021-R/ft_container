/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:20 by seojin            #+#    #+#             */
/*   Updated: 2022/12/16 11:34:33 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_HPP
#define VECTOR_HPP

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
		for(size_type i = 0; i < _size; ++i)
			_allocator.construct(&_vector[i], value);
	}
	template < class InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL) :
			_allocator(alloc), _vector(NULL), _size(0), _capacity(0)
	{
		// if (first <= last)
		// {
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
		// }
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
		{
			pointer tmp = _allocator.allocate(cnt);
			size_type i = 0;
			for(; i < cnt; ++i)
				_allocator.construct(&tmp[i], value);
			this->~vector();
			_capacity = cnt;
			_size = cnt;
			_vector = tmp;
		}
		else
		{
			for (iterator it = begin(); it != end(); ++it)
				_allocator.destroy(it.operator->());

			size_type i = 0;
			for (; i < cnt; ++i)
				_allocator.construct(&_vector[i], value);
			_size = i;
		}
	}
	template <class InputIt>
	void assign( InputIt first, InputIt last,
	typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 )
	{
		size_type cnt = 0;
		InputIt it = first;
		while (it != last)
		{
			++cnt;
			++it;
		}

		if (_capacity < cnt)
		{
			pointer tmp = _allocator.allocate(cnt);
			size_type i = 0;
			for(; first != last; ++first, ++i)
				_allocator.construct(&tmp[i], *first);
			if (_size)
				this->~vector();
			_capacity = cnt;
			_vector = tmp;
		}
		else
		{
			iterator vit = begin();
			for(; vit != end(); ++vit)
				_allocator.destroy(vit.operator->());
			
			for (int i = 0; first != last; ++first, ++i)
				_allocator.construct(&_vector[i], *first);
		}
		_size = cnt;
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
	const_iterator			begin( void ) const { return const_iterator(_vector); }
	iterator				begin( void ) { return iterator(_vector); }
	const_iterator			end( void ) const { return const_iterator(_vector + _size); }
	iterator				end( void ) { return iterator(_vector + _size); }
	
	// const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(_vector + _size - 1); }
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
		pointer tmp = _allocator.allocate(_capacity);

		size_type i = 0;
		const_iterator it = begin();
		while (it != pos)
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}
		
		_allocator.construct(&tmp[i], value);
		++i;

		while (it != end())
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}
		_size = i;
		this->~vector();
		_vector = tmp;
		return (_vector + diff);
	}
	void insert( const_iterator pos, size_type count, const_reference value )
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");


		// difference_type diff = pos - begin();
		while (_capacity < _size + count)
		{
			_capacity = _capacity ? _capacity *2 : 1;
		}

		pointer tmp = _allocator.allocate(_capacity);
		const_iterator it = begin();
		size_type i = 0;
		while (it != pos)
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}

		while (count)
		{
			_allocator.construct(&tmp[i], value);
			++i;
			--count;
		}

		while (it != end())
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}
		_size = i;
		this->~vector();
		_vector = tmp;
	}
	
	template <class InputIt>
	void insert( const_iterator pos, InputIt first, InputIt last,
	typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL )
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		// if (first > last)
		// 	throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");
		
		// difference_type diff = pos - begin();

		InputIt	tmpIt = first;
		size_t	tmpSize = 0;
		while (tmpIt != last)
		{
			++tmpIt;
			++tmpSize;
		}
		while (_capacity < _size + tmpSize)
			_capacity = _capacity ? _capacity * 2 : 1;
		
		pointer tmp = _allocator.allocate(_capacity);

		size_t i = 0;
		const_iterator it = begin();
		while (it != pos)
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}

		while (first != last)
		{
			_allocator.construct(&tmp[i], *first);
			++first;
			++i;
		}

		while (it != end())
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}

		_size = i;
		this->~vector();
		_vector = tmp;
	}

	iterator erase( iterator pos )
	{
		if (pos < begin() || pos > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - erase, OUT OF RANGE ERR");

		difference_type diff = pos - begin();
		pointer tmp = _allocator.allocate(_capacity);
		size_type i = 0;
		iterator it = begin();
		while (it != pos)
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}
		++it;
		while (it != end())
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}
		this->~vector();
		_vector = tmp;
		_size = i;
		return (iterator(_vector + diff));
	}
	iterator erase( iterator first, iterator last )
	{

		if (first < begin() || last > end())
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		if (first > last)
			throw std::out_of_range("Error: ft::vector<T, Alloc> - insert, OUT OF RANGE ERR");

		difference_type diff = first - begin();

		pointer tmp = _allocator.allocate(_capacity);
		iterator it = begin();
		size_t i = 0;

		while (it != first)
		{
			_allocator.construct(&tmp[i], *it);
			++it;
			++i;
		}

		while (it != last)
			++it;

		for(; it != end(); ++it, ++i)
			_allocator.construct(&tmp[i], *it);
		
		_size = i;
		this->~vector();
		_vector = tmp;

		return iterator(_vector + diff);
	}

	void push_back( const_reference value )
	{
		if (_size == _capacity)
		{
			_capacity ? _capacity *= 2 : _capacity = 1;

			pointer tmp = _allocator.allocate(_capacity);
			size_type i = 0;
			iterator it = begin();
			for(; it != end(); ++it, ++i)
				_allocator.construct(&tmp[i], *it);
			_allocator.construct(&tmp[i], value);
			++i;
			if (_size)
				this->~vector();
			_size = i;
			_vector = tmp;
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
		if (n < _capacity)
		{
			iterator it = begin();
			size_type i = 0;
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
				_capacity = _capacity ? _capacity * 2 : 1;


			pointer tmp = _allocator.allocate(_capacity);
			iterator it = begin();
			size_t i = 0;
			for(; it != end(); ++it, ++i)
				_allocator.construct(&tmp[i], *it);
			for(; i < n; ++i)
				_allocator.construct(&tmp[i], value);

			_size = n;
			this->~vector();
			_vector = tmp;
		}
	}
	void swap ( vector& other )
	{
		pointer			_tmpVector = other._vector;
		size_type		_tmpSize = other._size;
		size_type		_tmpCapacity = other._capacity;


		other._vector = _vector;
		other._size  = _size;
		other._capacity = _capacity;

		_vector = _tmpVector;
		_size = _tmpSize;
		_capacity = _tmpCapacity;
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
	lhs.swap(rhs);
}

template <class T, class Alloc>
bool operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return false;

	typename vector<T, Alloc>::const_iterator lit = lhs.begin();
	typename vector<T, Alloc>::const_iterator rit = rhs.begin();

	while (lit != lhs.end())
	{
		if (*lit != *rit) return false;
		++lit;
		++rit;
	}

	return true;
}

template <class T, class Alloc>
bool operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return true;
	
	typename vector<T, Alloc>::const_iterator lit = lhs.begin();
	typename vector<T, Alloc>::const_iterator rit = rhs.begin();
	
	while (lit != lhs.end())
	{
		if (*lit == *rit) return false;
		++lit;
		++rit;
	}
	
	return true;
}

template <class T, class Alloc>
bool operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	typename vector<T, Alloc>::const_iterator lit = lhs.begin();
	typename vector<T, Alloc>::const_iterator rit = rhs.begin();

	while (rit != rhs.end())
	{
		if (lit == lhs.end() || *rit > *lit) return false;
		else if (*lit > *rit) return true;
		++rit;
		++lit;
	}

	return (lit != lhs.end());
}

template <class T, class Alloc>
bool operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	typename vector<T, Alloc>::const_iterator lit = lhs.begin();
	typename vector<T, Alloc>::const_iterator rit = rhs.begin();

	while (lit != lhs.end())
	{
		if (rit == rhs.end() || *rit < *lit) return false;
		else if (*lit < *rit) return true;
		++rit;
		++lit;
	}

	return (rit != rhs.end());
}

template <class T, class Alloc>
bool operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	typename vector<T, Alloc>::const_iterator lit = lhs.begin();
	typename vector<T, Alloc>::const_iterator rit = rhs.begin();

	while (rit != rhs.end())
	{
		if (lit == lhs.end() || *lit < *rit) return false;
		else if (*lit > *rit) return true;
		++lit;
		++rit;
	}

	return true;
}


template <class T, class Alloc>
bool operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
{
	typename vector<T, Alloc>::const_iterator lit = lhs.begin();
	typename vector<T, Alloc>::const_iterator rit = rhs.begin();

	while (lit != lhs.end())
	{
		if (rit == rhs.end() || *lit > *rit) return false;
		else if (*lit < *rit) return true;
		++lit;
		++rit;
	}

	return true;
}




}


#endif