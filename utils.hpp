#ifndef UTILS_HPP
# define UTILS_HPP

#include <type_traits>
#include <algorithm>

namespace ft
{
	/* enable_if */

	template < bool, typename T = void >
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T	type;
	};

	/* is_integral */

	template <typename T>
	struct is_integral
	{
	};

	/* equal */

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
				return (false);
		}
		return (true);
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (pred(*first1, *first2))
				return (false);
		}
		return (true);
	};

	/* lexicographical_compare */

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2,	InputIterator2 last2)
	{
		for (; first2 != last2; ++first1, ++first2)
		{
			if (first1 == last1 || *first1 >= *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return (false);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for (; first2 != last2; ++first1, ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return (false);
	};
}

#endif
