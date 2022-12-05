/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:19 by seojin            #+#    #+#             */
/*   Updated: 2022/12/05 20:46:58 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>
#include "utility.hpp"
#include "map_iterator.hpp"

namespace ft
{
template<class Key, class T, class Compare = std::less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{

private:
	/* ====== Node definition ====== */
	struct Node
	{
		ft::pair<const Key, T>	content;
		Node*					parent;
		Node*					left;
		Node*					right;
	};

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
	typedef ft::map_iterator<Key, const T, Node>					iterator;
	typedef ft::map_iterator<Key, const T, Node>					const_iterator;



private:
	Node*					_root;
	Node*					_hub;
	size_type				_size;
	allocator_type			_pairAllocator;
	key_compare				_comp;
	std::allocator<Node>	_nodeAllocator;





	/* ====== private functions ====== */
	Node* newNode( value_type content )
	{
		Node* newNode = _nodeAllocator.allocate(1);

		_pairAllocator.construct(&newNode->content, content);
		newNode->parent = NULL;
		newNode->left = NULL;
		newNode->right = NULL;

		return newNode;
	}


	Node* searchNode( Node* head, key_type key )
	{
		if (!head || head == _hub)
			return NULL;

		if (!_comp(head->content.first, key) && !_comp(key, head->content.first))
			return head;

		if (_comp(key, head->content.first) && head->left && head->left != _hub)
			return searchNode(head->left, key);
		else if (_comp(head->content.first, key) && head->right && head->right != _hub)
			return searchNode(head->right, key);

		return NULL;
	}


	Node* insertNode( Node* pos, value_type val )
	{
		if (_root == _hub)
		{
			_root = newNode( val );

			_root->left = _hub;
			_root->right = _hub;
			_hub->left = _root;
			_hub->right = _root;

			return _root;
		}

		if (pos->content.first == val.first)
			return NULL;


		if (val.first < pos->content.first && pos->left && pos->left != _hub)
			return insertNode( pos->left, val );
		else if (val.first > pos->content.first && pos->right && pos->right != _hub)
			return insertNode( pos->right, val );


		Node* node = newNode( val );

		if (node->content.first < pos->content.first && !pos->left)
			pos->left = node;
		else if (node->content.first > pos->content.first && !pos->right)
			pos->right = node;
		else if (node->content.first < pos->content.first && pos->left)
		{
			pos->left = node;
			node->left = _hub;
			_hub->right = node;
		}
		else if (node->content.first > pos->content.first && pos->right)
		{
			pos->right = node;
			node->right = _hub;
			_hub->left = node;
		}
		node->parent = pos;

		balanceAdjustment(&_root, node);
		return node;
	}


	void	balanceAdjustment(Node** root, Node* newNode)
	{
		size_t	balanceFactor;

		while (newNode)
		{
			balanceFactor = getBalanceFactor(newNode);
			if (balanceFactor > 1 && getBalanceFactor(newNode->left) > 0)
			{
				RR(&_root, newNode);
			}
			else if (balanceFactor > 1)
			{
				LL(&_root, newNode->left);
				RR(&_root, newNode);
			}
			else if (balanceFactor < -1 && getBalanceFactor(newNode->right) > 0)
			{
				RR(&_root, newNode->right);
				LL(&_root, newNode);
			}
			else if (balanceFactor < -1)
			{
				LL(&_root, newNode);
			}
			newNode = newNode->parent;
		}
	}



	void RR(Node** _root, Node* parent)
	{
		Node* child = parent->left;
		Node* grandChild = child->right;

		child->right = parent;
		parent->left = grandChild;

		if (grandChild)
			grandChild->parent = parent;

		child->parent = parent->parent;
		parent->parent = child;

		if (!child->parent)
			*_root = child;
		else if (child->parent->right == parent)
			child->parent->right = child;
		else if (child->parent->left == parent)
			child->parent->left = child;
	}

	void LL(Node** _root, Node* parent)
	{
		Node* child = parent->right;
		Node* grandChild = child->left;

		child->left = parent;
		parent->right = grandChild;

		if (grandChild)
			grandChild->parent = parent;

		child->parent = parent->parent;
		parent->parent = child;

		if (!child->parent)
			*_root = child;
		else if (child->parent->right == parent)
			child->parent->right = child;
		else if (child->parent->left == parent)
			child->parent->left = child;
	}



	size_t	getBalanceFactor(Node* node)
	{
		size_t leftHeight, rightHeight;

		leftHeight = getNodeHeight(node->left, -1);
		rightHeight = getNodeHeight(node->right, -1);

		return leftHeight - rightHeight;
	}

	size_t	getNodeHeight(Node* node, size_t height)
	{
		size_t leftHeight, rightHeight;

		if (!node)
			return height;
		
		leftHeight = getNodeHeight(node->left, height + 1);
		rightHeight = getNodeHeight(node->right, height + 1);

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}



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
		bool operator()( const value_type& lhs, const value_type& rhs ) { return c( lhs, rhs ); }
	};





public:


	/* ====== Constructors & destructor ====== */

	explicit map( const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type()) :
		_size(0), _pairAllocator(alloc), _comp(comp)
	{
		_hub = newNode(ft::pair<const key_type, mapped_type>());
		_root = _hub;
		_root->left = _hub;
		_root->right = _hub;
	}

	template <class InputIt>
	map( InputIt first, InputIt last, 
		const Compare& comp = Compare(),
		const Allocator& alloc = Allocator() ) :
		_size(0), _pairAllocator(alloc), _comp(comp)
	{
		// insert 구현 필요.
	}

	map( const map& other ) :
		_size(0), _pairAllocator(other._pairAllocator),
		_nodeAllocator(other._nodeAllocator), _comp(other._comp)
	{
		// inser 구현 필요.
	}




	~map()
	{
		// clear 구현 필요.
	}



	map& operator=( const map& other )
	{
		map tmp(other);
		
		// swap 구현 필요.
	}










	/* ====== Iterators ====== */


	const_iterator	begin( void ) const { return const_iterator(_hub->right); }
	iterator		begin( void ) { return iterator(_hub->right); }
	const_iterator	end( void ) const { return const_iterator(_hub); }
	iterator		end( void ) { return iterator(_hub); }





	/* ====== Capacity ====== */
	bool		empty( void ) const { return _size == 0; }
	size_type	size( void ) const { return _size; }
	size_type	max_size( void ) const { return _pairAllocator.max_size(); }




	/* ====== Modifiers ====== */
	void clear( void )
	{
		
	}

	ft::pair<iterator, bool> insert( const value_type& value )
	{
		Node* tmp = searchNode(_root, value.first);

		if (tmp)
			return ft::pair<iterator, bool>(iterator(tmp, _hub), false);

		++_size;
		return ft::pair<iterator, bool>(iterator(insertNode(_root, value), _hub), true);
	}
	

	


};





}