/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:45:15 by seojin            #+#    #+#             */
/*   Updated: 2022/11/30 14:01:27 by seojin           ###   ########.fr       */
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

	pointer		getPtr( void ) const { return _ptr; }

	bool		operator==( const self& rai ) const { return _ptr == rai._ptr; }
	bool		operator!=( const self& rai ) const { return _ptr != rai._ptr; }

	reference	operator*( void ) const { return *_ptr; }
	pointer		operator->( void ) const { return _ptr; }

	self&		operator++( void ) { ++_ptr; return *this; }
	self		operator++( int ) { self tmp; tmp._ptr = _ptr; ++_ptr; return tmp; }
	self&		operator--( void ) { --_ptr; return *this; }
	self		operator--( int ) { self tmp; tmp._ptr = _ptr; --_ptr; return tmp; }

	self		operator+( difference_type n ) const { return self(_ptr + n); }
	self		operator-( const self& rai ) const { return self(_ptr - rai._ptr); }
	self		operator-( difference_type n ) const { return self(_ptr - n); }


	bool		operator<( const self& rai ) const { return _ptr < rai._ptr; }
	bool		operator>( const self& rai ) const { return _ptr > rai._ptr; }
	bool		operator<=( const self& rai ) const { return _ptr <= rai._ptr; }
	bool		operator>=( const self& rai ) const { return _ptr >= rai._ptr; }

	self&		operator+=( difference_type n ) { _ptr += n; return *this; }
	self&		operator-=( difference_type n ) { _ptr -= n; return *this; }

	reference	operator[]( difference_type n ) const { return *(_ptr + n); }
	operator	random_access_iterator<const T> () const { return random_access_iterator<const T>(_ptr); }

	random_access_iterator( const pointer ptr = NULL ) : _ptr(ptr) {}
	random_access_iterator( const self& rai ) : _ptr(rai._ptr) {}
	~random_access_iterator() {}
	random_access_iterator& operator=( const self& rai ) { _ptr = rai._ptr; return *this; }

protected:
	pointer	_ptr;


};

/* +operator commutative law */
template <class T>
typename ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai )
{
	return rai.getPtr() + n;
}



template <class Iterator>
class reverse_random_access_iterator
{

public:
	typedef Iterator 													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

	pointer base( void ) const { return _ptr; }

	reverse_random_access_iterator( const pointer ptr = NULL ) : _ptr(ptr) {}
	reverse_random_access_iterator( const reverse_random_access_iterator& other ) : _ptr(other._ptr) {}

	template <class T>
	explicit reverse_random_access_iterator( const ft::random_access_iterator<T>& other ) : _ptr(other.getPtr() - 1) {}

	~reverse_random_access_iterator() {}
	reverse_random_access_iterator &operator=( const reverse_random_access_iterator& other ) { _ptr = other._ptr; return *this; }

	reference operator*( void ) const { return *_ptr; }
	pointer operator->( void ) const { return _ptr; }

	reference operator[]( difference_type n ) const { return *(_ptr - n); }

	reverse_random_access_iterator& operator++( void ) { --_ptr; return *this; }
	reverse_random_access_iterator operator++( int ) { reverse_random_access_iterator tmp(_ptr); --_ptr; return tmp; }
	reverse_random_access_iterator& operator--( void ) { ++_ptr; return *this; }
	reverse_random_access_iterator operator--( int ) { reverse_random_access_iterator tmp(_ptr); ++_ptr; return tmp; }

	reverse_random_access_iterator operator+( difference_type n ) const { return _ptr - n; }
	reverse_random_access_iterator operator-( difference_type n ) const { return _ptr + n; }
	reverse_random_access_iterator& operator+= ( difference_type n ) { _ptr -= n; return *this; }
	reverse_random_access_iterator& operator-= ( difference_type n ) { _ptr += n; return *this; }

	
private:
	pointer _ptr;

};

template <class Iterator1, class Iterator2>
bool operator==( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return lhs == rhs; }

template <class Iterator1, class Iterator2>
bool operator!=( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return lhs != rhs; }

template <class Iterator1, class Iterator2>
bool operator>( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return lhs > rhs; }

template <class Iterator1, class Iterator2>
bool operator<( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return lhs < rhs; }

template <class Iterator1, class Iterator2>
bool operator>=( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return lhs >= rhs; }

template <class Iterator1, class Iterator2>
bool operator<=( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return lhs <= rhs; }

template <class Iterator>
reverse_random_access_iterator<Iterator> operator+( typename reverse_random_access_iterator<Iterator>::difference_type n, const reverse_random_access_iterator<Iterator>* it ) { return it->base() - n; }

template <class Iterator1, class Iterator2>
typename reverse_random_access_iterator<Iterator1>::difference_type operator-( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs ) { return rhs.base() - lhs.base(); }



};
