/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:20 by seojin            #+#    #+#             */
/*   Updated: 2022/11/29 15:51:38 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
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
	const_iterator	end( void ) const { return const_iterator(_vector + size); }
	iterator		end( void ) { return iterator(_vector + size); }

	vector() : _vector(NULL), size(0), capacity(0) {}
	explicit vector( const allocator_type& alloc ) {}
	explicit vector( size_type cnt, const T& value = T(), const Allocator& alloc = Allocator()) {}
	template < class InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator()) {}
	vector( const vector& ohter ) {}
	~vector() {}


private:
	allocator_type	allocator; 
	pointer			_vector;
	size_type		size;
	size_type		capacity;
};


}