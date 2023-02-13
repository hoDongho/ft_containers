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

	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
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

	template<typename Category, typename T, typename Distance = ptrdiff_t,
			typename Pointer = T*, typename Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/* reverse_iterator */

	template <typename Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator											iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::reference		reference;
		typedef typename iterator_traits<Iterator>::pointer			pointer;

		// Constructor
		reverse_iterator(): current() {};
		explicit reverse_iterator(Iterator x): current(x) {};

		//Copy Constructor, Assignment operator
		template <typename U> reverse_iterator(const reverse_iterator<U>& u)
			: current(u.base()) {};
		template <typename U> reverse_iterator& operator=(const reverse_iterator<U>& u)
		{
			current = u.base(); return (*this);
		};

		Iterator			base() const {
			return current;
		};

		//operator overloading
		reference			operator*() const {
			Iterator tmp = current;
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
			return (*this);
		};
		reverse_iterator	operator+ (difference_type n) const {
			return (reverse_iterator(current - n));
		};
		reverse_iterator&	operator+=(difference_type n) {
			current -= n;
			return (*this);
		};
		reverse_iterator	operator- (difference_type n) const {
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
		return (x.base() < y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() != y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() > y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() >= y.base());
	};

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return (x.base() <= y.base());
	};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		return (rhs.base() - lhs.base());
	};

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& x) {
		return reverse_iterator<Iterator>((x.base() - n));
	};
}

#endif
