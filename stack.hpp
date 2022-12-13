/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:15 by seojin            #+#    #+#             */
/*   Updated: 2022/12/13 11:42:04 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{


template <class T, class Container = ft::vector<T> >
class stack
{

public:
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;

protected:
	container_type c;



public:
	explicit stack( const container_type& container = container_type() ) : c(container) {}
	stack ( const stack& other ) : c(other.c) {}
	~stack() {}

	stack& operator=( const stack& other )
	{
		c = other.c;
		return *this;
	}

	bool empty() const { return(c.size() == 0); }
	size_type size() const { return c.size(); }

	value_type& top() { return c.back(); }
	const value_type& top() const { return c.back(); }

	void push( const value_type& value ) { c.push_back(value); }
	void pop() { c.pop_back(); }

	const container_type& getCtnr( void ) const { return c; }

};


template <class T, class Container>
bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
{
	return lhs.getCtnr() == rhs.getCtnr();
}

template <class T, class Container>
bool operator!=( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
{
	return lhs.getCtnr() != rhs.getCtnr();
}

template <class T, class Container>
bool operator>( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
{
	return lhs.getCtnr() > rhs.getCtnr();
}

template <class T, class Container>
bool operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
{
	return lhs.getCtnr() < rhs.getCtnr();
}

template <class T, class Container>
bool operator>=( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
{
	return lhs.getCtnr() >= rhs.getCtnr();
}

template <class T, class Container>
bool operator<=( const stack<T, Container>& lhs, const stack<T, Container>& rhs )
{
	return lhs.getCtnr() <= rhs.getCtnr();
}


}


#endif