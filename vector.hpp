#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"

// #include <vector>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef Alloc				allocator_type;
		protected:
			typedef T					value_type;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef value_type*			pointer;
			typedef const value_type*	const_pointer;
			typedef pointer				iterator;
			typedef const_pointer		const_iterator;
	};
}

#endif
