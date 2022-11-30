/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:20 by seojin            #+#    #+#             */
/*   Updated: 2022/11/30 10:54:53 by seojin           ###   ########.fr       */
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
	typedef T														value_type;
	typedef Allocator												allocator_type;
	typedef	typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::size_type						size_type;
	typedef typename allocator_type::difference_type				difference_type;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename ft::random_access_iterator<value_type>			iterator;
	typedef typename ft::random_access_iterator<const value_type>	const_iterator;
	// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;


	const_iterator	begin( void ) const { return const_iterator(_vector); }
	iterator		begin( void ) { return iterator(_vector); }
	const_iterator	end( void ) const { return const_iterator(_vector + _size); }
	iterator		end( void ) { return iterator(_vector + _size); }


	explicit vector( const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _vector(NULL), _size(0), _capacity(0) {}

	explicit vector( size_type cnt, const T& value = T(), const Allocator& alloc = Allocator()) :
				_alloc(alloc), _vector(NULL), _size(cnt), _capacity(cnt)
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
			size_type diff = last - first;

			_vector = _allocator.allocate(diff);
			_size = diff;
			_capacity = diff;

			for(int i = 0; first != last; ++first, ++i)
				_allocator.construct(&_vector[i], *first);
		}
	}


	vector( const vector& other ) :
			_allocator(other._allocator), _vector(NULL), _size(other._size), _capacity(other._capacity)
	{
		_vector = _allocator.allocate(_capacity);

		iterator it = other.begin();
		for(int i = 0; it != other.end(); ++it, ++i)
			_allocator.construct(&_vector[i], *it)
	}

	~vector()
	{
		for(iterator it = begin(); it != end(); ++it)
			_allocator.destruct(it.operator->());
		_allocator.deallocate(_vector, _capacity);
	}





private:
	allocator_type	_allocator; 
	pointer			_vector;
	size_type		_size;
	size_type		_capacity;
};


}