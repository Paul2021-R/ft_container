/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:09:01 by seojin            #+#    #+#             */
/*   Updated: 2022/12/16 17:21:35 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "vector.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{
	

template <class T>
struct vector_iterator : ft::iterator<ft::random_access_iterator_tag, T>
{

public:
	typedef	vector_iterator						self;
	typedef typename self::value_type			value_type;
	typedef typename self::pointer				pointer;
	typedef typename self::reference			reference;
	typedef typename self::difference_type		difference_type;
	typedef typename self::iterator_category	iterator_category;

	pointer			getPtr( void ) const { return _ptr; }


	reference		operator*( void ) const { return *_ptr; }
	pointer			operator->( void ) const { return _ptr; }

	self&			operator++( void ) { ++_ptr; return *this; }
	self			operator++( int ) { self tmp; tmp._ptr = _ptr; ++_ptr; return tmp; }
	self&			operator--( void ) { --_ptr; return *this; }
	self			operator--( int ) { self tmp; tmp._ptr = _ptr; --_ptr; return tmp; }

	self			operator+( difference_type n ) const { return self(_ptr + n); }
	self			operator-( difference_type n ) const { return self(_ptr - n); }
	difference_type	operator-( const self& rai ) const { return _ptr - rai._ptr; }

	template <class InputIt>
	bool			operator==( const InputIt& rai ) const { return _ptr == rai.getPtr(); }
	template <class InputIt>
	bool			operator!=( const InputIt& rai ) const { return _ptr != rai.getPtr(); }
	template <class InputIt>
	bool			operator<( const InputIt& rai ) const { return _ptr < rai.getPtr(); }
	template <class InputIt>
	bool			operator>( const InputIt& rai ) const { return _ptr > rai.getPtr(); }
	template <class InputIt>
	bool			operator<=( const InputIt& rai ) const { return _ptr <= rai.getPtr(); }
	template <class InputIt>
	bool			operator>=( const InputIt& rai ) const { return _ptr >= rai.getPtr(); }

	self&			operator+=( difference_type n ) { _ptr += n; return *this; }
	self&			operator-=( difference_type n ) { _ptr -= n; return *this; }

	reference		operator[]( difference_type n ) const { return *(_ptr + n); }
	operator		vector_iterator<const T> () const { return vector_iterator<const T>(_ptr); }

	vector_iterator( const pointer ptr = NULL ) : _ptr(ptr) {}
	vector_iterator( const self& rai ) : _ptr(rai._ptr) {}
	~vector_iterator() {}
	vector_iterator& operator=( const self& rai ) { _ptr = rai._ptr; return *this; }

protected:
	pointer	_ptr;


};

/* +operator commutative law */
template <class T>
typename ft::vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type n, typename ft::vector_iterator<T>& rai )
{
	return rai.getPtr() + n;
}





template <class Iterator>
class reverse_vector_iterator
{

public:
	typedef Iterator 													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;
	typedef typename ft::vector_iterator<const value_type>				cit;

	iterator_type	base( void ) const { return Iterator(_ptr + 1); }
	pointer			getPtr( void ) const { return _ptr; }

	reverse_vector_iterator( const pointer ptr = NULL ) : _ptr(ptr) {}
	reverse_vector_iterator( const reverse_vector_iterator& other ) : _ptr(other._ptr) {}

	// template <class InputIt>
	explicit reverse_vector_iterator( const Iterator& other ) : _ptr(other.getPtr() - 1) {}

	template <class InputIt>
	explicit reverse_vector_iterator( const InputIt& other, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* ) : _ptr(other.getPtr() - 1) {}


	~reverse_vector_iterator() {}
	reverse_vector_iterator &operator=( const reverse_vector_iterator& other ) { _ptr = other._ptr; return *this; }

	reference operator*( void ) const { return *_ptr; }
	pointer operator->( void ) const { return _ptr; }

	reference operator[]( difference_type n ) const { return *(_ptr - n); }

	reverse_vector_iterator& operator++( void ) { --_ptr; return *this; }
	reverse_vector_iterator operator++( int ) { reverse_vector_iterator tmp(_ptr); --_ptr; return tmp; }
	reverse_vector_iterator& operator--( void ) { ++_ptr; return *this; }
	reverse_vector_iterator operator--( int ) { reverse_vector_iterator tmp(_ptr); ++_ptr; return tmp; }

	reverse_vector_iterator operator+( difference_type n ) const { return _ptr - n; }
	reverse_vector_iterator operator-( difference_type n ) const { return _ptr + n; }
	reverse_vector_iterator& operator+= ( difference_type n ) { _ptr -= n; return *this; }
	reverse_vector_iterator& operator-= ( difference_type n ) { _ptr += n; return *this; }
	operator reverse_vector_iterator<cit> () const { return reverse_vector_iterator<cit>(_ptr); }
	
	
	
private:
	pointer _ptr;

};

template <class T>
typename ft::reverse_vector_iterator<T> operator+(typename ft::reverse_vector_iterator<T>::difference_type n, typename ft::reverse_vector_iterator<T>& rai )
{
	return rai.getPtr() - n;
}

template <class Iterator1, class Iterator2>
bool operator==( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return lhs.getPtr() == rhs.getPtr(); }

template <class Iterator1, class Iterator2>
bool operator!=( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return lhs.getPtr() != rhs.getPtr(); }

template <class Iterator1, class Iterator2>
bool operator<( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return lhs.getPtr() > rhs.getPtr(); }

template <class Iterator1, class Iterator2>
bool operator>( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return lhs.getPtr() < rhs.getPtr(); }

template <class Iterator1, class Iterator2>
bool operator<=( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return lhs.getPtr() >= rhs.getPtr(); }

template <class Iterator1, class Iterator2>
bool operator>=( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return lhs.getPtr() <= rhs.getPtr(); }

template <class Iterator>
reverse_vector_iterator<Iterator> operator+( typename reverse_vector_iterator<Iterator>::difference_type n, const reverse_vector_iterator<Iterator>* it ) { return it->getPtr() - n; }

template <class Iterator1, class Iterator2>
typename reverse_vector_iterator<Iterator1>::difference_type operator-( const reverse_vector_iterator<Iterator1>& lhs, const reverse_vector_iterator<Iterator2>& rhs ) { return rhs.getPtr() - lhs.getPtr(); }



};


#endif