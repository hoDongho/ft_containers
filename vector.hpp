#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "utils.hpp"

#include <vector>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef pointer										iterator;
			typedef const_pointer								const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		protected:
			pointer			_begin;
			pointer			_end;
			pointer			_end_cap;
			allocator_type	_alloc;

		public:
			/* Constructor */

			// explicit vector(const allocator_type& alloc)
			// 	: _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc) {}

			// explicit vector(size_type n, const value_type& value = value_type(),
			// 				const allocator_type& alloc = allocator_type())
			// 	: _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
			// {
			// }

			// template <typename InputIterator>
			// vector(InputIterator first, InputIterator last,
			// 		const allocator_type& alloc = allocator_type());
			// vector(const vector& copy);

			// ~vector();

			// vector&	operator=(const vector& copy);

			/* Iterator */

			iterator			begin() { return (iterator(_begin)); }
			iterator			end() { return (iterator(_end)); }
			reverse_iterator	rbegin() { return (reverse_iterator(_end)); }
			reverse_iterator	rend() { return (reverse_iterator(_begin)); }

			/* Capacity */

			size_type	size() const
			{
				return (static_cast<size_type>(_end - _begin));
			}

			size_type	max_size() const
			{
				return (std::min<size_type>(_alloc.max_size(),
											std::numeric_limits<difference_type>::max()));
			}

			size_type	capacity() const
			{
				return (_end_cap - _begin);
			}

			bool		empty() const
			{
				return (_begin == _end);
			}

			void		reserve(size_type n)
			{
				if (n > max_size())
					throw (std::length_error("vector"));
				if (n > capacity())
				{
					pointer new_begin, new_end;

					new_begin = new_end = _alloc.allocate(n);

					for (iterator i = _begin; i != _end; i++, new_end++)
						_alloc.construct(new_end, *i);

					_alloc.destroy(_begin);
					_alloc.deallocate(_begin, capacity());

					_begin = new_begin;
					_end = new_end;
					_end_cap = new_begin + n;
				}
			}

			void		resize(size_type n, value_type val = value_type())
			{
				if (n > max_size())
					throw (std::length_error("vector"));

				size_type s = size();

				if (n > capacity())
				{
					reserve(n);

					for (size_type cnt = 0;; cnt + 1 != n; _end++, cnt++)
						_alloc.construct(_end, val);
				}
				else if (n < size())
				{
					size_type	cap = n - capacity();
					_alloc.destroy(_begin + (cap));
					_alloc.deallocate(_begin + (cap), cap)
				}
			}

			/* Elements Access */

			reference			operator[](size_type n)
			{
				return (_begin[n]);
			}

			const_reference		operator[](size_type n) const
			{
				return (_begin[n]);
			}

			reference			at(size_type n)
			{
				if (n >= size())
					throw (std::out_of_range("vector"));
				return (_begin[i]);
			}

			const_reference		at(size_type n) const
			{
				if (n >= size())
					throw (std::out_of_range("vector"));
				return (_begin[i]);
			}

			reference			front()
			{
				return (*_begin);
			}

			const_reference		front() const
			{
				return (*_begin);
			}

			reference			back()
			{
				return (*(end - 1));
			}

			const_reference		back() const
			{
				return (*(end - 1));
			}

			value_type*			data();
			const value_type*	data() const;

			/* Modifiers */

			template <typename InputIterator>
			void		assign(InputIterator first, InputIterator last);
			void		assign(size_type n, const value_type& val);
			void		push_back(const value_type& x);
			void		pop_back();
			iterator	insert(const_iterator pos, const value_type& val);
			iterator	insert(const_iterator pos, size_type n, const value_type& val);
			template <typename InputIterator>
			iterator	insert(const_iterator pos, InputIterator first, InputIterator last);
			iterator	erase(const_iterator pos);
			iterator	erase(const_iterator first, const_iterator last);
			void		swap(vector& other);
			void		clear();
	};

	template <typename T, typename Alloc>
	bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template <typename T, typename Alloc>
	bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template <typename T, typename Alloc>
	bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template <typename T, typename Alloc>
	bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template <typename T, typename Alloc>
	bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	template <typename T, typename Alloc>
	bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template <typename T, typename Alloc>
	void	swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs);
}

#endif
