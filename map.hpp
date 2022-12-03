/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:19 by seojin            #+#    #+#             */
/*   Updated: 2022/12/03 10:46:04 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>
#include "utility.hpp"

namespace ft
{
template<class Key, class T, class Compare = std::less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T>>>
class map
{



public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef pair<const key_type, mapped_type>						value_type;
	typedef Compare													key_compare;
	typedef Allocator												allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename allocator_type::size_type						size_type;
	typedef typename allocator_type::difference_type				difference_type;

	// typedef typename ft::bidirectional_iterator<value_type>			iterator;
	// typedef typename ft::bidirectional_iterator<const value_type>	const_iterator;

private:
	class Node
	{
		value_type	content;
		Node*		parent;
		Node*		left;
		Node*		right;
	};


public:
	class value_compare
	{
		friend class map;

	protected:
		key_compare	comp;
		
		value_compare(Compare c) : comp(c) {}

	public:
		typedef bool		result_type;
		typedef value_type	first;
		typedef value_type	second;
		bool operator( void )( const vlaue_type& lhs, const value_type& rhs ) { return c( lhs, rhs ); }
	}

	


};





}