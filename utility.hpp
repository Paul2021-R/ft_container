/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:24:15 by seojin            #+#    #+#             */
/*   Updated: 2022/12/15 21:58:31 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{

/* === enable_if === */
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T>
{
	typedef T	type;
};



/* === integral_constant === */
template <class T, T v>
struct integral_constant
{
	static const T value = v;
    typedef T value_type;
    typedef integral_constant type;
    operator value_type() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


/* === is_integral === */
template <class T> struct is_integral : public false_type {};
template <class T> struct is_integral<const T> : public is_integral<T> {};
// template <class T> struct is_integral<volatile T> : public is_integral<T> {};
// template <class T> struct is_integral<volatile const T> : public is_integral<T> {};

template<> struct is_integral<unsigned char> : public true_type {};
template<> struct is_integral<unsigned short> : public true_type {};
template<> struct is_integral<unsigned int> : public true_type {};
template<> struct is_integral<unsigned long> : public true_type {};
template<> struct is_integral<signed char> : public true_type {};
template<> struct is_integral<short> : public true_type {};
template<> struct is_integral<int> : public true_type {};
template<> struct is_integral<long> : public true_type {};
template<> struct is_integral<char> : public true_type {};
template<> struct is_integral<bool> : public true_type {};
template<> struct is_integral<char16_t> : public true_type {};
template<> struct is_integral<char32_t> : public true_type {};
template<> struct is_integral<wchar_t> : public true_type {};







/* === pair === */
template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;
    second_type second;


    /* === Constructors === */
    pair() : first(first_type()), second(second_type()) {}
    template <class U, class V>
    pair( const pair<U, V>& pr ) : first(pr.first), second(pr.second) {}
    pair( const first_type& a, const second_type& b ) : first(a), second(b) {}


    /* === Copy Assignment === */
    pair& operator=( const pair& other ) { first = other.first; second = other.second; return *this; }
    
};


template <class T1, class T2>
pair<T1, T2> make_pair( T1 t, T2 u )
{
    return pair<T1, T2>(t, u);
}



template <class T1, class T2>
bool operator==( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) { return (lhs.first == rhs.first && lhs.second == rhs.second); }

template <class T1, class T2>
bool operator!=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) { return (lhs.first != rhs.first || lhs.second != rhs.second); }

template <class T1, class T2>
bool operator>( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
{
    if (lhs.first > rhs.first) return true;
    if (lhs.first < rhs.first) return false;
    if (lhs.second > rhs.second) return true;
    if (lhs.second < rhs.second) return false;
    return false;
}

template <class T1, class T2>
bool operator<( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
{
    if (lhs.first < rhs.first) return true;
    if (lhs.first > rhs.first) return false;
    if (lhs.second < rhs.second) return true;
    if (lhs.second > rhs.second) return false;
    return false;
}

template <class T1, class T2>
bool operator>=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
{
    if (lhs.first >= rhs.first) return true;
    if (lhs.first <= rhs.first) return false;
    if (lhs.second >= rhs.second) return true;
    if (lhs.second <= rhs.second) return false;
    return false;
}

template <class T1, class T2>
bool operator<=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs )
{
    if (lhs.first <= rhs.first) return true;
    if (lhs.first >= rhs.first) return false;
    if (lhs.second <= rhs.second) return true;
    if (lhs.second >= rhs.second) return false;
    return false;
}

}

#endif