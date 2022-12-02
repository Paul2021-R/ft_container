/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojin <seojin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:36:22 by seojin            #+#    #+#             */
/*   Updated: 2022/12/02 13:45:24 by seojin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP


namespace ft
{

template <class InputIt1, class InputIt2>
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	while (first1 != last1)
	{
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}


template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
{
	while (first1 != last1)
	{
		if (!p(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}



}



#endif