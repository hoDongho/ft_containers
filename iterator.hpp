#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	/* iterator category */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* iterator_traits */

	template <typename Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	/* iterator */

	template <typename Category, typename T, typename Distance = ptrdiff_t,
			typename Pointer = T*, typename Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/* reverse_iterator */

	template <typename Iter>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference>
	{
	protected:
		Iter current;
	public:
		typedef Iter											iterator_type;
		typedef typename iterator_traits<Iter>::difference_type	difference_type;
		typedef typename iterator_traits<Iter>::reference		reference;
		typedef typename iterator_traits<Iter>::pointer			pointer;

		// Constructor
		reverse_iterator(): current() {};
		explicit reverse_iterator(Iter x): current(x) {};

		//Copy Constructor, Assignment operator
		template <typename U> reverse_iterator(const reverse_iterator<U>& u)
			: current(u.base()) {};
		template <typename U> reverse_iterator& operator=(const reverse_iterator<U>& u)
		{
			current = u.base(); return (*this);
		};

		Iter			base() const {
			return current;
		};

		//operator overloading
		reference			operator*() const {
			Iter tmp = current;
			return (*--tmp);
		};
		pointer				operator->() const {
			return (&operator*());
		};
		reverse_iterator&	operator++() {
			--current;
			return (*this);
		};
		reverse_iterator	operator++(int) {
			reverse_iterator	tmp(*this);
			--current;
			return (tmp);
		};
		reverse_iterator&	operator--() {
			++current;
			return (*this);
		};
		reverse_iterator	operator--(int) {
			reverse_iterator	tmp(*this);
			++current;
			return (tmp);
		};
		reverse_iterator	operator+(difference_type n) const {
			return (reverse_iterator(current - n));
		};
		reverse_iterator&	operator+=(difference_type n) {
			current -= n;
			return (*this);
		};
		reverse_iterator	operator-(difference_type n) const {
			return (reverse_iterator(current + n));
		};
		reverse_iterator&	operator-=(difference_type n) {
			current += n;
			return (*this);
		};
		reference			operator[](difference_type n) const {
			return (*(*this + n));
		};
	};

	//Comparison operator

	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() == y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() > y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() != y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() < y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() <= y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() >= y.base());
	};

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs,
			const reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
	};

	template <typename Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
			const reverse_iterator<Iter>& x) {
		return reverse_iterator<Iter>((x.base() - n));
	};

}

#endif
