#ifndef UTILS_HPP
# define UTILS_HPP

#include <type_traits>

namespace ft
{
	/* enable_if */

	template <bool, typename T = void >
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T	type;
	};

	/* integral_constant */

	template<typename T, T v>
	struct integral_constant
	{
		static const T				value = v;
		typedef T					value_type;
		typedef	integral_constant	type;
		operator value_type() {return (value);};
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	/* is_integral */

	template <typename T>	struct is_integral						: public false_type {};
	template <>				struct is_integral<bool>				: public true_type {};
	template <>				struct is_integral<char>				: public true_type {};
	template <>				struct is_integral<signed char>			: public true_type {};
	template <>				struct is_integral<unsigned char>		: public true_type {};
	template <>				struct is_integral<char16_t>			: public true_type {};
	template <>				struct is_integral<char32_t>			: public true_type {};
	template <>				struct is_integral<wchar_t>				: public true_type {};
	template <>				struct is_integral<short>				: public true_type {};
	template <>				struct is_integral<unsigned short>		: public true_type {};
	template <>				struct is_integral<int>					: public true_type {};
	template <>				struct is_integral<unsigned int>		: public true_type {};
	template <>				struct is_integral<long>				: public true_type {};
	template <>				struct is_integral<unsigned long>		: public true_type {};
	template <>				struct is_integral<long long>			: public true_type {};
	template <>				struct is_integral<unsigned long long>	: public true_type {};

	/* equal */

	template <typename Iter1, typename Iter2>
	bool	equal(Iter1 first1, Iter1 last1, Iter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
				return (false);
		}
		return (true);
	};

	template <typename Iter1, typename Iter2, typename BinaryPredicate>
	bool	equal(Iter1 first1, Iter1 last1,
		Iter2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (pred(*first1, *first2))
				return (false);
		}
		return (true);
	};

	/* lexicographical_compare */

	template <typename Iter1, typename Iter2>
	bool	lexicographical_compare(Iter1 first1, Iter1 last1,
		Iter2 first2,	Iter2 last2)
	{
		for (; first2 != last2; ++first1, ++first2)
		{
			if (first1 == last1 || *first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return (false);
	}

	template <typename Iter1, typename Iter2, typename Compare>
	bool	lexicographical_compare(Iter1 first1, Iter1 last1,
		Iter2 first2, Iter2 last2, Compare comp)
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

	/* pair */

	template <typename T1, typename T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	_first;
		second_type	_second;

		pair() : _first(), _second() {};
		pair(T1 const& t1, T2 const& t2) : _first(t1), _second(t2) {};

		template <typename U1, typename U2>
		pair(const pair<U1, U2>& p) : _first(p._first), _second(p._second) {};

		pair&	operator=(pair const& p) {
			_first = p._first;
			_second = p._second;
			return (*this);
		}
	};

	template <typename T1, typename T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs._first == rhs._first && lhs._second == rhs._second);
	};

	template <typename T1, typename T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!(lhs == rhs));
	};

	template <typename T1, typename T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs._first < rhs._first || ((!(rhs._first < lhs._first)) && lhs._second < rhs._second));
	};

	template <typename T1, typename T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (rhs < lhs);
	};

	template <typename T1, typename T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!(rhs < lhs));
	};

	template <typename T1, typename T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!(lhs < rhs));
	};

	/* make_pair */

	template <typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) {
		return (pair<T1, T2>(x, y));
	};

	/* less */

	template<typename T>
	struct less
	{
		bool	operator()(const T& lhs, const T& rhs)
		{
			return (lhs < rhs);
		}
	};
}

#endif
