/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:16:19 by seojin            #+#    #+#             */
/*   Updated: 2022/12/16 17:26:50 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_HPP
#define MAP_HPP

#include <stdexcept>
#include <memory>
#include <iostream>
#include "utility.hpp"
#include "map_iterator.hpp"
#include "algorithm.hpp"
#include <sys/time.h>

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
		int						height;
	};

public:
	typedef Key																key_type;
	typedef T																mapped_type;
	typedef pair<const key_type, mapped_type>								value_type;
	typedef Compare															key_compare;
	typedef Allocator														allocator_type;
	typedef typename allocator_type::reference								reference;
	typedef typename allocator_type::const_reference						const_reference;
	typedef typename allocator_type::pointer								pointer;
	typedef typename allocator_type::const_pointer							const_pointer;
	typedef typename allocator_type::size_type								size_type;
	typedef typename allocator_type::difference_type						difference_type;
	typedef ft::map_iterator<Key, T, Node, value_type, key_compare>			iterator;
	typedef ft::map_iterator<Key, T, Node, const value_type, key_compare>	const_iterator;
	typedef ft::reverse_map_iterator<iterator, Node, key_compare>			reverse_iterator;
	typedef ft::reverse_map_iterator<const_iterator, Node, key_compare>		const_reverse_iterator;


private:
	Node*					_root;
	Node*					_hub;
	size_type				_size;
	allocator_type			_pairAllocator;
	key_compare				_comp;
	std::allocator<Node>	_nodeAllocator;





	/* ====== private functions ====== */
	Node*	newNode( value_type content )
	{
		Node* newNode = _nodeAllocator.allocate(1);

		_pairAllocator.construct(&newNode->content, content);
		newNode->parent = NULL;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 0;
		return newNode;
	}
	Node*	searchNode( Node* head, const key_type& key ) const
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
	Node*	insertNode( Node* pos, value_type val )
	{
		if (_root == _hub)
		{
			_root = newNode( val );

			_root->left = _hub;
			_root->right = _hub;
			_hub->left = _root;
			_hub->right = _root;
			_root->height = 1;

			return _root;
		}

		// if (pos->content.first == val.first)
		if (!_comp(pos->content.first, val.first) && !_comp(val.first, pos->content.first))
			return NULL;

		// if (_hub->right->content.first > val.first)
		if (_comp(val.first, _hub->right->content.first))
		{
			pos = _hub->right;
		}
		// else if (_hub->left->content.first < val.first)
		else if (_comp(_hub->left->content.first, val.first))
		{
			pos = _hub->left;
		}
		else
		{
			while (1)
			{
				// if (pos->content.first > val.first)
				if (_comp(val.first, pos->content.first))
				{
					if (!pos->left || pos->left == _hub)
						break;
					pos = pos->left;
				}
				// else if (pos->content.first < val.first)
				else if (_comp(pos->content.first, val.first))
				{
					if(!pos->right || pos->right == _hub)
						break;
					pos = pos->right;
				}
			}
		}

		Node* node = newNode( val );

		// if (node->content.first < pos->content.first && !pos->left)
		if (_comp(node->content.first, pos->content.first) && !pos->left)
			pos->left = node;
		// else if (node->content.first > pos->content.first && !pos->right)
		else if (_comp(pos->content.first, node->content.first) && !pos->right)
			pos->right = node;
		// else if (node->content.first < pos->content.first && pos->left)
		else if (_comp(node->content.first, pos->content.first) && pos->left)
		{
			pos->left = node;
			node->left = _hub;
			_hub->right = node;
		}
		// else if (node->content.first > pos->content.first && pos->right)
		else if (_comp(pos->content.first, node->content.first) && pos->right)
		{
			pos->right = node;
			node->right = _hub;
			_hub->left = node;
		}
		node->parent = pos;

		updateHeightUp(node);
		balanceAdjustment(&_root, node);
		return node;
	}
	void updateHeightUp(Node* node)
	{
		int left = 0;
		int right = 0;

		while (node)
		{
			(node->left && node->left != _hub) ? left = node->left->height : left = 0;
			(node->right && node->right != _hub) ? right = node->right->height : right = 0;

			node->height = left > right ? left + 1 : right + 1;
			node = node->parent;
		}
	}
	void updateHeightDown(Node* node)
	{
		if (!node || node == _hub)
			return ;
		
		int left, right;

		left = getNodeHeight(node->left, 0);
		right = getNodeHeight(node->right, 0);

		node->height = left > right ? left + 1 : right + 1;
		updateHeightDown(node->left);
		updateHeightDown(node->right);
	}

	bool	deleteNode( Node* pos, key_type key)
	{
		
		Node* tmp = searchNode(pos, key);

		if (!tmp)
			return false;

		/*
		1. root 이고, 자식이 둘 다 없는경우.
		2. root 이고, 왼쪽 자식만 있는 경우.
		3. root 이고, 오른쪽 자식만 있는 경우.
		*/

		if (tmp == _root)
		{
			if (tmp->left == _hub && tmp->right == _hub)
			{
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				_root = _hub;
				_root->right = _hub;
				_root->left = _hub;
				return true;
			}

			if (tmp->right == _hub)
			{
				_root = tmp->left;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				_root->right = _hub;
				return true;
			}

			if (tmp->left == _hub)
			{
				_root = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				_root->left = _hub;
				return true;
			}

			Node* max = maxNode(tmp->left);

			_pairAllocator.destroy(&tmp->content);
			_pairAllocator.construct(&tmp->content, max->content);
			return deleteNode(tmp->left, max->content.first);
		}


		/* 말단 노드인 경우*/
		if ((!tmp->left || tmp->left == _hub) && (!tmp->right || tmp->right == _hub))
		{
			/*
			1. 왼쪽 말단 노드에 자식이 없는 경우.
			2. 왼쪽 말단 노드에 자식이 있는 경우.
			3. 오른쪽 말단 노드에 자식이 없는 경우.
			4. 오른쪽 말단 노드에 자식이 있는 경우.
			*/

			Node* tmpParent = tmp->parent;

			if (tmp->left == _hub && !tmp->right)
			{
				tmp->parent->left = _hub;
				_hub->right = tmp->parent;
			}
			else if (tmp->left == _hub && tmp->right)
			{
				tmp->parent->left = tmp->right;
				_hub->right = tmp->right;
				tmp->right->parent = tmp->parent;
				tmp->right->left = _hub;
			}
			else if (tmp->right == _hub && !tmp->left)
			{
				tmp->parent->right = _hub;
				_hub->left = tmp->parent;
			}
			else if (tmp->right == _hub && tmp->left)
			{
				tmp->parent->right = tmp->left;
				_hub->left = tmp->left;
				tmp->left->parent = tmp->parent;
				tmp->left->right = _hub;
			}
			else if (!tmp->left && !tmp->right)
			{
				if (tmp->content.first <= tmp->parent->content.first)
				{
					tmp->parent->left = NULL;
				}
				else
				{
					tmp->parent->right = NULL;
				}
			}
			_pairAllocator.destroy(&tmp->content);
			_nodeAllocator.deallocate(tmp, 1);
			updateHeightUp(tmpParent);
			balanceAdjustment(&_root, tmpParent);
			return true;
		}

		/*
		1. 자식이 둘 다 없는 경우.
		*/
		if ((!tmp->left && !tmp->right))
		{
			Node* tmpParent = tmp->parent;

			if (tmp->content.first < tmp->parent->content.first)
				tmp->parent->left = NULL;
			else if (tmp->content.first > tmp->parent->content.first)
				tmp->parent->right = NULL;
			
			_pairAllocator.destroy(&tmp->content);
			_nodeAllocator.deallocate(tmp, 1);

			updateHeightUp(tmpParent);
			balanceAdjustment(&_root, tmpParent);
			return true;
		}
		


		/*
		1. 왼쪽 자식만 있는 경우.
		3. 오른쪽 자식만 있는 경우.
		4. 둘 다 있는 경우.
		*/

		if (tmp->left && tmp->left != _hub && !tmp->right)
		{
			Node* tmpParent = tmp->parent;

			if (tmp->content.first <= tmp->parent->content.first)
			{
				tmp->left->parent = tmp->parent;
				tmp->parent->left = tmp->left;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}

			if (tmp->content.first > tmp->parent->content.first)
			{
				tmp->left->parent = tmp->parent;
				tmp->parent->right = tmp->left;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}
		}

		if (tmp->left && tmp->left == _hub && tmp->right)
		{
			Node* tmpParent = tmp->parent;

			if (tmp->content.first <= tmp->parent->content.first)
			{
				tmpParent->left = tmp->right;
				tmp->right->left = _hub;
				tmp->right->parent = tmpParent;
				_hub->right = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}

			if (tmp->content.first > tmp->parent->content.first)
			{
				tmpParent->right = tmp->right;
				tmp->right->left = _hub;
				tmp->right->parent = tmpParent;
				_hub->right = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}
		}

		if (tmp->right && tmp->right == _hub && tmp->left)
		{
			Node* tmpParent = tmp->parent;

			if (tmp->content.first <= tmp->parent->content.first)
			{
				tmpParent->left = tmp->left;
				tmp->left->right = _hub;
				tmp->left->parent = tmpParent;
				_hub->left = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}

			if (tmp->content.first > tmp->parent->content.first)
			{
				tmpParent->right = tmp->left;
				tmp->left->right = _hub;
				tmp->left->parent = tmpParent;
				_hub->left = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}
		}

		if (tmp->right && tmp->right != _hub && !tmp->left)
		{
			Node* tmpParent = tmp->parent;

			if (tmp->content.first < tmp->parent->content.first)
			{
				tmp->right->parent = tmp->parent;
				tmp->parent->left = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}

			if (tmp->content.first > tmp->parent->content.first)
			{
				tmp->right->parent = tmp->parent;
				tmp->parent->right = tmp->right;
				_pairAllocator.destroy(&tmp->content);
				_nodeAllocator.deallocate(tmp, 1);
				updateHeightUp(tmpParent);
				balanceAdjustment(&_root, tmpParent);
				return true;
			}
		}


		if (tmp->right && tmp->right != _hub && tmp->left && tmp->left != _hub)
		{
			Node* max = maxNode(tmp->left);
			_pairAllocator.destroy(&tmp->content);
			_pairAllocator.construct(&tmp->content, max->content);

			
			return deleteNode(tmp->left, max->content.first);
		}
		return true;
	}
	void	balanceAdjustment(Node** root, Node* newNode)
	{
		int balanceFactor;
		while (newNode)
		{
			balanceFactor = getBalanceFactor(newNode);
			if (balanceFactor > 1 && getBalanceFactor(newNode->left) > 0)
			{
				RR(root, newNode);
			}
			else if (balanceFactor > 1)
			{
				LL(root, newNode->left);
				RR(root, newNode);
			}
			else if (balanceFactor < -1 && getBalanceFactor(newNode->right) > 0)
			{
				RR(root, newNode->right);
				LL(root, newNode);
			}
			else if (balanceFactor < -1)
			{
				LL(root, newNode);
			}
			newNode = newNode->parent;
		}
	}

	void	RR(Node** _root, Node* parent)
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
		updateHeightUp(parent);
	}
	void	LL(Node** _root, Node* parent)
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
		updateHeightUp(parent);
	}
	int		getBalanceFactor(Node* node)
	{
		int left, right;

		node->left ? left = node->left->height : left = 0;
		node->right ? right = node->right->height : right = 0;

		return left - right;
	}
	int		getNodeHeight(Node* node, long height)
	{
		int leftHeight, rightHeight;

		if (!node || node == _hub)
			return height;
		
		leftHeight = getNodeHeight(node->left, height + 1);
		rightHeight = getNodeHeight(node->right, height + 1);

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}

	Node*	minNode(Node* node)
	{
		if (node->left && node->left != _hub)
			return minNode(node->left);
		return node;
	}
	Node*	maxNode(Node* node)
	{
		if (node->right && node->right != _hub)
			return maxNode(node->right);
		return node;
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
		bool operator()( const value_type& lhs, const value_type& rhs ) const
		{
			return comp( lhs.first, rhs.first );
		}
	};



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
		_hub = newNode(ft::pair<const key_type, mapped_type>());
		_root = _hub;
		_root->right = _hub;
		_root->left = _hub;
		for (; first != last; ++first)
			insert(*first);
	}
	map( const map& other ) :
		_size(0), _pairAllocator(other._pairAllocator),
		_comp(other._comp), _nodeAllocator(other._nodeAllocator)
	{
		_hub = newNode(ft::pair<const key_type, mapped_type>());
		_root = _hub;
		_root->right = _hub;
		_root->left = _hub;
		const_iterator it = other.begin();
		for(; it != other.end(); ++ it)
			insert(*it);
	}


	~map()
	{
		clear();
		_pairAllocator.destroy(&_hub->content);
		_nodeAllocator.deallocate(_hub, 1);
	}

	map& operator=( const map& other )
	{
		clear();

		const_iterator it = other.begin();
		for (; it != other.end(); ++it)
			insert(*it);
		_size = other._size;
		return *this;
	}





	/* ====== Element ====== */
	T& at( const Key& key )
	{
		Node* tmp = searchNode(_root, key);

		if (tmp)
			return tmp->content.second;
		throw std::out_of_range("Error: out of range.");
	}

	const T& at( const Key& key ) const
	{
		Node* tmp = searchNode(_root, key);

		if (tmp)
			return tmp->content.second;
		throw std::out_of_range("Error: out of range.");
	}

	T& operator[]( const Key& key )
	{
		Node* tmp = searchNode(_root, key);

		if (tmp)
			return tmp->content.second;
		
		pair<iterator, bool> _pair = insert(pair<Key, T>(key, mapped_type()));
		return _pair.first->second;
	}


	/* ====== Iterators ====== */
	const_iterator			begin( void ) const { return const_iterator(_hub->right, _hub); }
	iterator				begin( void ) { return iterator(_hub->right, _hub); }
	const_iterator			end( void ) const { return const_iterator(_hub, _hub); }
	iterator				end( void ) { return iterator(_hub, _hub); }
	const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(_hub->left, _hub); }
	reverse_iterator		rbegin( void ) { return reverse_iterator(_hub->left, _hub); }
	const_reverse_iterator	rend( void ) const { return const_reverse_iterator(_hub, _hub); }
	reverse_iterator		rend( void ) { return reverse_iterator(_hub, _hub); }



	/* ====== Capacity ====== */
	bool		empty( void ) const { return _size == 0; }
	size_type	size( void ) const { return _size; }
	size_type	max_size( void ) const { return _pairAllocator.max_size(); }



	/* ====== Modifiers ====== */
	void erase( iterator pos )
	{
		deleteNode(pos.getNode(), pos->first);
		--_size;
	}
	void erase( iterator first, iterator last )
	{
		while (first != last)
		{
			iterator tmp(first);
			++first;
			erase(tmp);
		}
	}
	size_type erase( const Key& key )
	{
		size_type result = deleteNode(_root, key);
		_size -= result;
		return result;
	}


	void clear( void )
	{
		erase(begin(), end());
	}

	void swap( map& other )
	{
		Node* _tmpRoot = other._root;
		Node* _tmpHub = other._hub;
		size_type _tmpSize = other._size;
		allocator_type _tmpPairAlloc = other._pairAllocator;
		key_compare _tmpKeyComp = other._comp;
		std::allocator<Node> _tmpNodeAlloc = other._nodeAllocator;

		other._root = _root;
		other._hub = _hub;
		other._size = _size;
		other._pairAllocator = _pairAllocator;
		other._nodeAllocator = _nodeAllocator;
		other._comp = _comp;

		_root = _tmpRoot;
		_hub = _tmpHub;
		_size = _tmpSize;
		_pairAllocator = _tmpPairAlloc;
		_nodeAllocator = _tmpNodeAlloc;
		_comp = _tmpKeyComp;
	}
	ft::pair<iterator, bool> insert( const value_type& value )
	{
		Node* tmp = searchNode(_root, value.first);

		if (tmp)
			return ft::pair<iterator, bool>(iterator(tmp, _hub), false);

		++_size;
		return ft::pair<iterator, bool>(iterator(insertNode(_root, value), _hub), true);
	}
	iterator insert( iterator pos, const value_type& value )
	{
		Node* tmp = searchNode(_root, value.first);

		if (tmp)
			return iterator(tmp, _hub);

		if (pos.getNode() == _hub && value.first < _root->content.first)
			pos = iterator(_hub->right, _hub);
		else if (pos.getNode() == _hub && value.first > _root->content.first)
			pos = iterator(_hub->left, _hub);

		if (value.first > pos.getNode()->content.first)
		{
			iterator next(pos);
			++next;
			while (next.getNode() && next.getNode() != _hub && next.getNode()->content.first < value.first)
			{
				++next;
				++pos;
			}

			++_size;
			return iterator(insertNode(pos.getNode(), value), _hub);
		}

		if (value.first < pos.getNode()->content.first)
		{
			iterator prev(pos);
			--prev;
			while (prev.getNode() && prev.getNode() != _hub && prev.getNode()->content.first > value.first)
			{
				--prev;
				--pos;
			}

			++_size;
			return iterator(insertNode(pos.getNode(), value), _hub);
		}

		return iterator(insertNode(_root, value), _hub);
	}
	template <class InputIt>
	void insert( InputIt first, InputIt last)
	{
		for(; first != last; ++first)
			insert(*first);
	}




	/* ====== LookUp ====== */
	size_type count( const Key& key )
	{
		Node* tmp = searchNode(_root, key);

		return tmp ? 1 : 0;
	}
	size_type count( const Key& key ) const
	{
		Node* tmp = searchNode(_root, key);

		return tmp ? 1 : 0;
	}
	iterator find( const Key& key )
	{
		Node* tmp = searchNode(_root, key);

		if (tmp)
			return iterator(tmp, _hub);
		return end();
	}
	const_iterator find( const Key& key ) const
	{
		Node* tmp = searchNode(_root, key);

		if (tmp)
			return const_iterator(tmp, _hub);
		return end();
	}
	iterator lower_bound( const Key& key )
	{
		iterator it = begin();

		for(; it != end(); ++it)
			if (it->first >= key)
				break;

		return it;
	}
	const_iterator lower_bound( const Key& key ) const
	{
		const_iterator it = begin();

		while ( it != end() && it->first < key)
			++it;

		return it;
	}
	iterator upper_bound( const Key& key )
	{
		iterator it = begin();

		for(; it != end(); ++it)
			if (key < it->first)
				break;

		return it;
	}
	
	const_iterator upper_bound( const Key& key ) const
	{
		const_iterator it = begin();

		for(; it != end(); ++it)
			if (key < it->first)
				break;

		return it;
	}
	pair<iterator, iterator> equal_range( const Key& key )
	{
		return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
	}
	pair<const_iterator, const_iterator> equal_range( const Key& key ) const
	{
		return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	}



	/* ====== Observer ====== */
	key_compare key_comp() const { return _comp; }
	value_compare value_comp() const { return value_compare(_comp); }

};


template <class Key, class T, class Compare, class Allocator>
void swap(ft::map<Key, T, Compare, Allocator>& lhs, ft::map<Key, T, Compare, Allocator>& rhs)
{
	lhs.swap(rhs);
}



template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return false;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();

	for(; lit != lhs.end(); ++lit, ++rit)
	{
		if (lit->first != rit->first)
			return false;
	}

	return true;
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return true;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();

	for(; lit != lhs.end(); ++lit, ++rit)
	{
		if (lit->first == rit->first)
			return false;
	}

	return true;
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();

	while (rit != rhs.end())
	{
		if (lit == lhs.end()) return false;
		else if (rit->first > lit->first) return false;
		else if (rit->first < lit->first) return true;
		else if (rit->first == lit->first && rit->second > lit->second) return false;
		else if (rit->first == lit->first && rit->second < lit->second) return true;
		++rit;
		++lit;
	}

	return (lit != lhs.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();

	while (rit != rhs.end())
	{
		if (lit == lhs.end()) return true;
		else if (rit->first < lit->first) return false;
		else if (rit->first > lit->first) return true;
		else if (rit->first == lit->first && rit->second < lit->second) return false;
		else if (rit->first == lit->first && rit->second > lit->second) return true;
		++rit;
		++lit;
	}

	return (rit != rhs.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();

	while (rit != rhs.end())
	{
		if (lit == lhs.end()) return false;
		else if (rit->first > lit->first) return false;
		else if (rit->first < lit->first) return true;
		else if (rit->first == lit->first && rit->second > lit->second) return false;
		else if (rit->first == lit->first && rit->second < lit->second) return true;
		++rit;
		++lit;
	}

	return true;
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();

	while (rit != rhs.end())
	{
		if (lit == lhs.end()) return true;
		else if (rit->first < lit->first) return false;
		else if (rit->first > lit->first) return true;
		else if (rit->first == lit->first && rit->second < lit->second) return false;
		else if (rit->first == lit->first && rit->second > lit->second) return true;
		++rit;
		++lit;
	}

	return (lit == lhs.end());
}



}

#endif