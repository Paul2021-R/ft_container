/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:36:15 by seojin            #+#    #+#             */
/*   Updated: 2022/12/17 17:21:19 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "utility.hpp"
#include <iostream>

namespace ft
{


template <class Key, class T, class Node, class Pair, class Comp>
struct map_iterator : ft::iterator<ft::bidirectional_iterator_tag, Pair >
{


public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef Comp										comp;
	typedef typename map_iterator::value_type			value_type;
	typedef typename map_iterator::difference_type		difference_type;
	typedef typename map_iterator::iterator_category	iterator_category;
	typedef typename map_iterator::reference			reference;
	typedef typename map_iterator::pointer				pointer;


private:
	Node*		_node;
	Node*		_last;
	comp		_comp;



public:
	map_iterator(Node* node = NULL, Node* last = NULL) :
	_node(node), _last(last) {}

	map_iterator(const map_iterator<Key, T, Node, Pair, Comp>& other) :
	_node(other._node), _last(other._last) {}

	~map_iterator() {}

	map_iterator& operator=( const map_iterator<Key, T, Node, Pair, Comp>& other )
	{
		_node = other._node;
		_last = other._last;
		return *this;
	}



	reference operator*( void ) const { return _node->content; }
	pointer operator->( void ) const { return &_node->content; }

	map_iterator& operator++( void )
	{
		if (_node && _node == _last)
		{
			_node = NULL;
			return *this;
		}

		if (_node && _node->right)
		{
			_node = _node->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return *this;
		}

		// if (_node && _node->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent;
			return *this;
		}

		if (_node && _node->parent && _node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			// while (_node->content.first > _node->parent->content.first)
			while (_comp(_node->parent->content.first, _node->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return *this;
		}

		if (_node && _node->parent && !_node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return *this;
		}

		return *this;
	}
	map_iterator operator++( int )
	{
		map_iterator tmp(*this);

		if (_node && _node == _last)
		{
			_node = NULL;
			return tmp;
		}

		if (_node && _node->right)
		{
			_node = _node->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return tmp;
		}

		// if (_node && _node->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			// while (_node->content.first > _node->parent->content.first)
			while (_comp(_node->parent->content.first, _node->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return tmp;
		}

		return tmp;
	}
	map_iterator& operator--( void )
	{
		if (_node && _node == _last)
		{
			_node = _node->left;
			return *this;
		}

		if (_node && _node->left)
		{
			_node = _node->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return *this;
		}

		// if (_node && _node->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent &&_comp(_node->parent->content.first,  _node->content.first))
		{
			_node = _node->parent;
			return *this;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			// while (_node->content.first < _node->parent->content.first)
			while (_comp(_node->content.first, _node->parent->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return *this;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return *this;
		}

		return *this;
	}
	map_iterator operator--( int )
	{
		map_iterator tmp(*this);

		if (_node && _node == _last)
		{
			_node = _node->left;
			return tmp;
		}

		if (_node && _node->left)
		{
			_node = _node->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return tmp;
		}

		// if (_node && _node->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			// while (_node->content.first < _node->parent->content.first)
			while (_comp(_node->content.first, _node->parent->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return tmp;
		}

		return *this;
	}
	
	template <class InputIt>
	bool operator==( const InputIt& it ) const { return it.getNode() == _node; }

	template <class InputIt>
	bool operator!=( const InputIt& it ) const { return it.getNode() != _node; }


	operator map_iterator<Key, T, Node, const Pair, Comp>() const { return map_iterator<Key, T, Node, const Pair, Comp>(_node, _last); }


	Node*	getNode( void ) const { return _node; }
	Node*	getLast( void ) const { return _last; }
	comp	getComp( void ) const { return _comp; }
};




template <class Iterator, class Node, class Comp>
class reverse_map_iterator
{
public:
	typedef Iterator 													iterator_type;
	typedef Comp														comp;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;
	typedef typename value_type::first_type								key;
	typedef typename value_type::second_type							mapped_value;
	typedef typename ft::map_iterator<key, mapped_value, Node, const value_type, comp> cit;


private:
	Node*	_node;
	Node*	_last;
	comp	_comp;

public:
	reverse_map_iterator(Node* node = NULL, Node* last = NULL) : _node(node), _last(last) {}
	reverse_map_iterator(const reverse_map_iterator& other) : _node(other._node), _last(other._last) {}
	~reverse_map_iterator() {}
	reverse_map_iterator& operator=( const reverse_map_iterator& other )
	{
		_node = other._node;
		_last = other._last;
		_comp = other._comp;
		return *this;
	}


	template <class InputIt>
	reverse_map_iterator( const InputIt& other ) : _node(other.getNode()), _last(other.getLast()), _comp(other.getComp()) {}


	reverse_map_iterator( const iterator_type& other ) : _node(other.getNode()), _last(other.getLast()), _comp(other.getComp())
	{
		iterator_type it(_node, _last);
		--it;
		_node = it.getNode();
	}


	iterator_type base( void ) const
	{
		reverse_map_iterator rit(_node, _last);
		--rit;
		iterator_type it(rit.getNode(), _last);

		return it;
	}


	reference operator*( void ) const { return _node->content; }
	pointer operator->( void ) const { return &_node->content; }
	
	reverse_map_iterator& operator--( void )
	{
		if (_node && _node == _last)
		{
			_node = _node->right;
			return *this;
		}

		if (_node && _node->right)
		{
			_node = _node->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return *this;
		}

		// if (_node && _node->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent;
			return *this;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			// while (_node->content.first > _node->parent->content.first)
			while (_comp(_node->parent->content.first, _node->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return *this;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return *this;
		}

		return *this;
	}
	reverse_map_iterator operator--( int )
	{
		reverse_map_iterator tmp(*this);

		if (_node && _node == _last)
		{
			_node = _node->right;
			return tmp;
		}

		if (_node && _node->right)
		{
			_node = _node->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return tmp;
		}

		// if (_node && _node->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			// while (_node->content.first > _node->parent->content.first)
			while (_comp(_node->parent->content.first, _node->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return tmp;
		}

		return tmp;
	}
	reverse_map_iterator& operator++( void )
	{
		if (_node && _node == _last)
		{
			_node = NULL;
			return *this;
		}

		if (_node && _node->left)
		{
			_node = _node->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return *this;
		}

		// if (_node && _node->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent;
			return *this;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			// while (_node->content.first < _node->parent->content.first)
			while (_comp(_node->content.first, _node->parent->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return *this;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return *this;
		}

		return *this;
	}
	reverse_map_iterator operator++( int )
	{
		reverse_map_iterator tmp(*this);

		if (_node && _node == _last)
		{
			_node = NULL;
			return tmp;
		}

		if (_node && _node->left)
		{
			_node = _node->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return tmp;
		}

		// if (_node && _node->parent && _node->content.first > _node->parent->content.first)
		if (_node && _node->parent && _comp(_node->parent->content.first, _node->content.first))
		{
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && _node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && _node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			// while (_node->content.first < _node->parent->content.first)
			while (_comp(_node->content.first, _node->parent->content.first))
				_node = _node->parent;
			_node = _node->parent;
			return tmp;
		}

		// if (_node && _node->parent && !_node->parent->parent && _node->content.first < _node->parent->content.first)
		if (_node && _node->parent && !_node->parent->parent && _comp(_node->content.first, _node->parent->content.first))
		{
			_node = _node->parent->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return tmp;
		}

		
		return *this;
	}


	operator reverse_map_iterator<cit, Node, Comp>() const { return reverse_map_iterator<cit, Node, Comp>(_node, _last); }
	

	template <class InputIt>
	bool operator==( const InputIt& it ) const { return it.getNode() == _node; }
	
	template <class InputIt>
	bool operator!=( const InputIt& it ) const { return it.getNode() != _node; }

	Node*	getNode( void ) const { return _node; }
	Node*	getLast( void ) const { return _last; }
	comp	getComp( void ) const { return _comp; }
};



}



#endif