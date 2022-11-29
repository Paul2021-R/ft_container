/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:45:15 by seojin            #+#    #+#             */
/*   Updated: 2022/11/29 10:23:03 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"

namespace ft
{
	

template <class T>
struct random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
{

public:
	typedef	random_access_iterator				self;
	typedef typename self::value_type			value_type;
	typedef typename self::pointer				pointer;
	typedef typename self::reference			reference;
	typedef typename self::difference_type		difference_type;
	typedef typename self::iterator_category	iterator_category;

	pointer		getPtr( void ) const { return ptr; }

	bool		operator==( const self& rai ) const { return ptr == rai.ptr; }
	bool		operator!=( const self& rai ) const { return ptr != rai.ptr; }

	reference	operator*( void ) const { return *ptr; }
	pointer		operator->( void ) const { return ptr; }

	self&		operator++( void ) { ++ptr; return *this; }
	self		operator++( int ) { self tmp; tmp.ptr = ptr; ++ptr; return tmp; }
	self&		operator--( void ) { --ptr; return *this; }
	self		operator--( int ) { self tmp; tmp.ptr = ptr; --ptr; return tmp; }

	self		operator+( difference_type n ) const { return self(ptr + n); }
	self		operator-( const self& rai ) const { return self(ptr - rai.ptr); }
	self		operator-( difference_type n ) const { return self(ptr - n); }


	bool		operator<( const self& rai ) const { return ptr < rai.ptr; }
	bool		operator>( const self& rai ) const { return ptr > rai.ptr; }
	bool		operator<=( const self& rai ) const { return ptr <= rai.ptr; }
	bool		operator>=( const self& rai ) const { return ptr >= rai.ptr; }

	self&		operator+=( difference_type n ) { ptr += n; return *this; }
	self&		operator-=( difference_type n ) { ptr -= n; return *this; }

	reference	operator[]( difference_type n ) const { return *(ptr + n); }
	operator	random_access_iterator<const T> () const { return random_access_iterator<const T>(ptr); }

	random_access_iterator( const pointer ptr = NULL ) : ptr(ptr) {}
	random_access_iterator( const self& rai ) : ptr(rai.ptr) {}
	~random_access_iterator() {}
	random_access_iterator &operator=( const self& rai ) { ptr = rai.ptr; return *this; }

protected:
	pointer	ptr;


};

/* +operator commutative law */
template <class T>
typename ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai )
{
	return rai.getPtr() + n;
}



};
