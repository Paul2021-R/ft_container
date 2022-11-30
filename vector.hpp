/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:20 by seojin            #+#    #+#             */
/*   Updated: 2022/11/30 13:57:39 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <exception>
#include "random_access_iterator.hpp"
#include "utility.hpp"

namespace ft
{

template < class T, class Allocator = std::allocator<T> >
class vector
{
public:
	typedef T															value_type;
	typedef Allocator													allocator_type;
	typedef	typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::difference_type					difference_type;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef typename ft::random_access_iterator<value_type>				iterator;
	typedef typename ft::random_access_iterator<const value_type>		const_iterator;
	typedef typename ft::reverse_random_access_iterator<iterator>		reverse_iterator;
	typedef typename ft::reverse_random_access_iterator<const_iterator>	const_reverse_iterator;






	/* ====== Constructors & Desctructor ====== */
	explicit vector( const allocator_type& alloc = allocator_type()) :
				_allocator(alloc), _vector(NULL), _size(0), _capacity(0) {}
	explicit vector( size_type cnt, const T& value = T(), const Allocator& alloc = Allocator()) :
				_allocator(alloc), _vector(NULL), _size(cnt), _capacity(cnt)
	{
		_vector = _allocator.allocate(cnt);
		
		for(int i = 0; i < cnt; ++i)
			_allocator.construct(&_vector[i], value);
	}
	template < class InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL) :
			_allocator(alloc), _vector(NULL), _size(0), _capacity(0)
	{
		if (first <= last)
		{
			size_t size = 0;
			iterator tmp = first;
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
		for(int i = 0; it != other.end(); ++it, ++i)
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
		for (int i = 0; it != other.end(); ++it, ++i)
			_allocator.construct(&_vector[i], *it);

		return *this;
	}




	const_iterator	begin( void ) const { return const_iterator(_vector); }
	iterator		begin( void ) { return iterator(_vector); }
	const_iterator	end( void ) const { return const_iterator(_vector + _size); }
	iterator		end( void ) { return iterator(_vector + _size); }
	
	const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(_vector + _size - 1); }
	reverse_iterator		rbegin( void ) { return reverse_iterator(_vector + _size - 1); }
	const_reverse_iterator	rend( void ) const { return const_reverse_iterator(_vector - 1); }
	reverse_iterator		rend( void ) { return reverse_iterator(_vector - 1); }









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