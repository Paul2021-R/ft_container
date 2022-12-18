/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __tree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haryu <haryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:12:35 by haryu             #+#    #+#             */
/*   Updated: 2022/12/18 21:40:26 by haryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP
#define __TREE_HPP

#include <memory>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

#define FT_NOEXCEPT thorw()

namespace ft {

enum __tree_node_color { RED = false, BLACK = true };

struct __tree_node_base;

__tree_node_base * __tree_increment(__tree_node_base * __x) FT_NOEXCEPT;
const __tree_node_base * __tree_increment(const __tree_node_base * __x) FT_NOEXCEPT;

__tree_node_base * __tree_decrement(__tree_node_base *__x) FT_NOEXCEPT;
const __tree_node_base * __tree_decrement(__tree_node_base *__x) FT_NOEXCEPT;

void __tree_rotate_left(const __tree_node_base * __x, const __tree_node_base *&__root);
void __tree_rotate_right(const __tree_node_base * __x, const __tree_node_base *&__root);

void __tree_insert_and_fixup(const bool __insert_left, __tree_node_base * __x, __tree_header * __p, __tree_node_base *&__root) FT_NOEXCEPT;

__tree_node_base * __tree_erase_and_fixup(const __tree_node_base * __z, __tree_node_base & __header) FT_NOEXCEPT;

__tree_node_base * __minimum(__tree_node_base * __x) FT_NOEXCEPT;
const __tree_node_base * __minimum(const __tree_node_base * __x) FT_NOEXCEPT;
__tree_node_base * __maximum(__tree_node_base * __x) FT_NOEXCEPT;
const __tree_node_base * __maximum(const __tree_node_base * __x) FT_NOEXCEPT;

/**
 * @brief tree 노드들 
 * 
 */
// RB 트리 구현을 위한 노드 구조체의 기반 
struct __tree_node_base {
	typedef __tree_node_base *_Base_ptr;
	typedef const __tree_node_base *_Const_base_ptr;

	__tree_node_color __color_;
	_Base_ptr __parent_;
	_Base_ptr __left_;
	_Base_ptr __right_;
};

// 트리 헤더 
struct __tree_header {
	__tree_node_base __header_;
	size_t __node_cout_;

	__tree_header() {
		__header_.__color_ = RED;
		__tree_reset();
	}

	void __tree_reset();
	void __tree_move_data(__tree_header & other);
};

template <typename _Key_compare>
struct __tree_kee_compare {
	_Key_compare __key;
	
	__tree_key_compare() : __key() {}
	__tree_key_compare(const _Key_compare & other) : __key(other) {}
};

// RB 트리 실제 노드
template <typename _Val>
struct __tree_node : public __tree_node_base {
	typedef __tree_node<_Val> * _Link_type;

	_Val __value_field;
	_Val * __valptr() { return & __value_field; }
	const _Val * __valptr() const { return & __value_field; }
};

/**
 * @brief Tree 노드 반복자
 * 
 */

template <typename _T>
struct __tree_iterator : public iterator<bidirectional_iterator_tag, _T> {
	typedef _T value_type;
	typedef _T& reference;
	typedef _T* pointer;
	typedef bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t differnece_type;

	typedef __tree_iterator<_T> iterator_type;
	typedef __tree_node_base::_Base_ptr _Base_ptr;
	typedef __tree_node<_T> * _Link_type;

	_Base_ptr __node_;

	__tree_iterator() : __node_() {}
	__tree_iterator(const __tree_iterator & other) : __node_(other.__node_) {}
	explicit __tree_iterator(_Base_ptr __x): __node_(__x) {}
	reference operator*() const FT_NOEXCEPT {
		return *static_cast<_Link_type>(__node_)->__valptr();
	}

	pointer operator->() const FT_NOEXCEPT {
		return staic_cast<_Link_type>(__node_)->__valptr();
	}

};

}

#endif