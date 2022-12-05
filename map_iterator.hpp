/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:36:15 by seojin            #+#    #+#             */
/*   Updated: 2022/12/05 20:50:08 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{


template <class Key, class T, typename Node>
struct map_iterator : ft::iterator<ft::bidirectional_iterator_tag, ft::pair<const Key, T> >
{



public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef typename map_iterator::value_type			value_type;
	typedef typename map_iterator::difference_type		difference_type;
	typedef typename map_iterator::iterator_category	iterator_category;
	typedef typename map_iterator::reference			reference;
	typedef typename map_iterator::pointer				pointer;


private:
	Node*		_node;
	Node*		_last;



public:
	map_iterator(Node* node = NULL, Node* last = NULL) :
	_node(node), _last(last) {}

	map_iterator(const map_iterator<Key, T, Node>& other) :
	_node(other._node), _last(other._last) {}

	~map_iterator() {}

	map_iterator& operator=( const map_iterator& other )
	{
		_node = other._node;
		_last = other._last;
		return *this;
	}



	reference operator*( void ) const { return _node->content; }
	pointer operator->( void ) const { return &_node->content; }

	map_iterator& operator++( void )
	{
		if (_node == _last)
		{
			_node = NULL;
			return *this;
		}

		if (_node->right)
		{
			_node = _node->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return *this;
		}

		if (_node->parent && _node->content.first < _node->parent->content.first)
		{
			_node = _node->parent;
			return *this;
		}

		if (_node->parent && _node->parent->parent && _node->content.first > _node->parent->content.first)
		{
			_node = _node->parent->parent;
			return *this;
		}

		if (_node->parent && !_node->parent->parent && _node->content.first > _node->parent->content.first)
		{
			_node = _node->parent->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return *this;
		}

		return *this;
	}
	map_iterator& operator++( int )
	{
		map_iterator tmp(*this);

		if (_node == _last)
		{
			_node = NULL;
			return tmp;
		}

		if (_node->right)
		{
			_node = _node->right;
			while (_node->left && _node != _last)
				_node = _node->left;
			return tmp;
		}

		if (_node->parent && _node->content.first < _node->parent->content.first)
		{
			_node = _node->parent;
			return tmp;
		}

		if (_node->parent && _node->parent->parent && _node->content.first > _node->parent->content.first)
		{
			_node = _node->parent->parent;
			return tmp;
		}

		if (_node->parent && !_node->parent->parent && _node->content.first > _node->parent->content.first)
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
		if (_node == _last)
		{
			_node = NULL;
			return *this;
		}

		if (_node->left)
		{
			_node = _node->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return *this;
		}

		if (_node->parent && _node->content.first > _node->parent->content.first)
		{
			_node = _node->parent;
			return *this;
		}

		if (_node->parent && _node->parent->parent && _node->content.first < _node->parent->content.first)
		{
			_node = _node->parent->parent;
			return *this;
		}

		if (_node->parent && !_node->parent->parent && _node->content.first < _node->parent->content.first)
		{
			_node = _node->parent->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return *this;
		}

		return *this;
	}
	map_iterator& operator--( int )
	{
		map_iterator tmp(*this);

		if (_node == _last)
		{
			_node = NULL;
			return tmp;
		}

		if (_node->left)
		{
			_node = _node->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return tmp;
		}

		if (_node->parent && _node->content.first > _node->parent->content.first)
		{
			_node = _node->parent;
			return tmp;
		}

		if (_node->parent && _node->parent->parent && _node->content.first < _node->parent->content.first)
		{
			_node = _node->parent->parent;
			return tmp;
		}

		if (_node->parent && !_node->parent->parent && _node->content.first < _node->parent->content.first)
		{
			_node = _node->parent->left;
			while (_node->right && _node != _last)
				_node = _node->right;
			return tmp;
		}

		return *this;
	}
	
	bool operator==( const map_iterator& it ) const { return it._node == _node; }
	bool operator!=( const map_iterator& it ) const { return it._node != _node; }


	operator map_iterator<Key, const T, Node>() const { return map_iterator<Key, const T, Node>(_node, _last); }

};






}



#endif