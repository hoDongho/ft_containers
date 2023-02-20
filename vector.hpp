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

	explicit vector(const allocator_type& alloc = allocator_type())
		: _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc) {}

	explicit vector(size_type n, const value_type& value = value_type(),
					const allocator_type& alloc = allocator_type())
		: _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
	{
		if (n > 0)
		{
			_begin = _end = _alloc.allocate(n);
			for (size_type cnt = 0; cnt < n; cnt++, ++_end)
				_alloc.construct(_end, value);
			_end_cap = _begin + n;
		}
	}

	template <typename Iter>
	vector(Iter first, Iter last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0)
		: _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
	{
		for (; first != last; ++first)
			push_back(*first);
	}

	vector(const vector& copy)
		: _begin(NULL), _end(NULL), _end_cap(NULL)
	{
		size_type size = copy.size();

		if (size > 0)
		{
			_begin = _end = _alloc.allocate(size);
			_end_cap = _begin + size;

			for (const_iterator i = copy.begin(); i != copy.end(); ++i, ++_end)
				_alloc.construct(_end, *i);

		}
	}

	~vector()
	{
		clear();
		if (_begin)
			_alloc.deallocate(_begin, capacity());
	}

	vector&	operator=(const vector& copy)
	{
		if (this != &copy)
			assign(copy.begin(), copy.end());
		return *this;
	}

	/* Iterator */

	iterator				begin() { return (iterator(_begin)); }
	iterator				end() { return (iterator(_end)); }
	const_iterator			begin() const { return (const_iterator(_begin)); }
	const_iterator			end() const { return (const_iterator(_end)); }

	reverse_iterator		rbegin() { return (reverse_iterator(_end)); }
	reverse_iterator		rend() { return (reverse_iterator(_begin)); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_end)); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(_begin)); }

	/* Capacity */

	size_type	size() const
	{
		return (static_cast<size_type>(_end - _begin));
	}

	size_type	max_size() const
	{
		size_type	maxSize = _alloc.max_size();
		size_type	diffTypeMax = static_cast<size_type>(std::numeric_limits<difference_type>::max());

		return (maxSize < diffTypeMax ? maxSize : diffTypeMax);
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

			for (iterator i = _begin; i != _end; ++i, ++new_end)
				_alloc.construct(new_end, *i);

			clear();
			if (_begin)
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

		if (n > size())
		{
			reserve(n);
			for (size_type cnt = size(); cnt < n; ++cnt, ++_end)
				_alloc.construct(_end, val);
		}
		else if (n < size())
		{
			for (size_type cnt = size(); cnt > n; --cnt, --_end)
				_alloc.destroy(_end - 1);
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
		return (_begin[n]);
	}

	const_reference		at(size_type n) const
	{
		if (n >= size())
			throw (std::out_of_range("vector"));
		return (_begin[n]);
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
		return (*(_end - 1));
	}

	const_reference		back() const
	{
		return (*(_end - 1));
	}

	/* Modifiers */

	template <typename Iter>
	void		assign(Iter first, Iter last,
			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0)
	{
		clear();
		for (; first != last; ++first)
			push_back(*first);
	}

	void		assign(size_type n, const value_type& val)
	{
		clear();
		if (n <= capacity())
		{
			for (size_type i = 0; i < n; i++)
				push_back(val);
		}
		else
		{
			pointer	new_begin, new_end;

			new_begin = new_end = _alloc.allocate(n);
			for (size_type cnt = 0; cnt < n; cnt++, ++new_end)
				_alloc.construct(new_end, val);

			if (_begin)
				_alloc.deallocate(_begin, capacity());

			_begin = new_begin;
			_end = new_end;
			_end_cap = new_begin + n;
		}
	}

	void		push_back(const value_type& x)
	{
		if (_end == _end_cap)
			reserve(recommend(size() + 1));
		_alloc.construct(_end, x);
		++_end;
	}

	void		pop_back()
	{
		_alloc.destroy(_end - 1);
		--_end;
	}

	iterator	insert(const_iterator position, const value_type& val)
	{
		pointer	pos = _begin + (position - begin());

		if (_end < _end_cap)
		{
			for (iterator i = _end; i != pos; --i)
			{
				_alloc.construct(i, *(i - 1));
				_alloc.destroy(i - 1);
			}
			_alloc.construct(pos, val);
			++_end;
		}
		else
		{
			pointer	new_begin, new_end, tmp_pos = pos;
			size_type	new_size = recommend(size() + 1);

			new_begin = new_end = _alloc.allocate(new_size);

			for (iterator i = _begin; i != tmp_pos; ++i, ++new_end)
				_alloc.construct(new_end, *i);

			pos = new_end;
			_alloc.construct(new_end, val);
			++new_end;

			for (iterator i = tmp_pos; i != _end; ++i, ++new_end)
				_alloc.construct(new_end, *i);

			clear();
			if (_begin)
				_alloc.deallocate(_begin, capacity());

			_begin = new_begin;
			_end = new_end;
			_end_cap = new_begin + new_size;
		}
		return (iterator(pos));
	}

	iterator	insert(const_iterator position, size_type n, const value_type& val)
	{
		pointer	pos = _begin + (position - begin());

		if (n > 0)
		{
			if (n <= static_cast<size_type>(_end_cap - _end))
			{
				for (iterator i = _end - 1 + n; i + 1 - n != pos; --i)
				{
					_alloc.construct(i, *(i - n));
					_alloc.destroy(i - n);
				}

				_end += n;

				iterator tmp_pos = pos;

				for (size_type i = 0; i < n; ++i, ++tmp_pos)
					_alloc.construct(tmp_pos, val);
			}
			else
			{
				pointer		new_begin, new_end, tmp_pos = pos;
				size_type	new_size = recommend(size() + n);

				new_begin = new_end = _alloc.allocate(new_size);

				for (iterator i = _begin; i != tmp_pos; ++i, ++new_end)
					_alloc.construct(new_end, *i);

				pos = new_end;
				for (size_type i = 0; i < n; ++i, ++new_end)
					_alloc.construct(new_end, val);

				for (iterator i = tmp_pos; i != _end; ++i, ++new_end)
					_alloc.construct(new_end, *i);

				clear();
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = new_begin;
				_end = new_end;
				_end_cap = new_begin + new_size;
			}
		}
		return (iterator(pos));
	}

	template <typename Iter>
	iterator	insert(const_iterator position, Iter first, Iter last,
				typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = 0)
	{
		pointer		pos = _begin + (position - begin());
		size_type	n = 0;

		for(Iter i = first; i != last; ++i, ++n);

		if (n > 0)
		{
			if (n <= static_cast<size_type>(_end_cap - _end))
			{
				for (iterator i = _end - 1 + n; i + 1 - n != pos; --i)
				{
					_alloc.construct(i, *(i - n));
					_alloc.destroy(i - n);
				}

				_end += n;

				iterator tmp_pos = pos;

				for (; first != last; ++tmp_pos, ++first)
					_alloc.construct(tmp_pos, *first);
			}
			else
			{
				pointer	new_begin, new_end, tmp_pos = pos;
				size_type	new_size = recommend(size() + n);

				new_begin = new_end = _alloc.allocate(new_size);

				for (iterator i = _begin; i != tmp_pos; ++i, ++new_end)
					_alloc.construct(new_end, *i);

				pos = new_end;
				for (; first != last; ++first, ++new_end)
					_alloc.construct(new_end, *first);

				for (iterator i = tmp_pos; i != _end; ++i, ++new_end)
					_alloc.construct(new_end, *i);

				clear();
				if (_begin)
					_alloc.deallocate(_begin, capacity());

				_begin = new_begin;
				_end = new_end;
				_end_cap = new_begin + new_size;
			}
		}
		return (iterator(pos));
	}

	iterator	erase(const_iterator position)
	{
		difference_type	pos = position - begin();
		pointer			ptr = _begin + pos;

		for (iterator i = ptr; i + 1 != _end; ++i)
			*i = *(i + 1);

		--_end;
		_alloc.destroy(_end);
		return (iterator(ptr));
	}

	iterator	erase(const_iterator first, const_iterator last)
	{
		pointer		ptr = _begin + (first - begin());
		size_type	distance = last - first;

		for (iterator i = ptr; i + distance != _end; ++i)
			*i = *(i + distance);

		for (; distance > 0; --_end, --distance)
			_alloc.destroy(_end - 1);

		return (iterator(ptr));
	}

	void		swap(vector& other)
	{
		if (this == &other)
			return ;

		pointer	tmp_begin = this->_begin;
		pointer	tmp_end = this->_end;
		pointer	tmp_end_cap = this->_end_cap;
		allocator_type& tmp_alloc = this->_alloc;

		this->_begin = other._begin;
		this->_end = other._end;
		this->_end_cap = other._end_cap;
		this->_alloc = other._alloc;

		other._begin = tmp_begin;
		other._end = tmp_end;
		other._end_cap = tmp_end_cap;
		other._alloc = tmp_alloc;
	}

	void		clear()
	{
		size_t	s = size();
		for (size_t i = 0; i < s; i++)
			_alloc.destroy(_begin + i);
		_end = _begin;
	}

	size_type	recommend(size_type	new_size)
	{
		const size_type	maxSize = max_size(), cap = capacity();

		if (new_size > maxSize)
			throw(std::length_error("vector"));
		if (cap >= maxSize / 2)
			return (maxSize);
		return (cap * 2 > new_size ? cap * 2 : new_size);
	}

	allocator_type get_allocator() const
	{
		return (_alloc);
	}
};

template <typename T, typename Alloc>
bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	if (lhs.size() == rhs.size())
	{
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}
	return (false);
}

template <typename T, typename Alloc>
bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <typename T, typename Alloc>
bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename Alloc>
bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <typename T, typename Alloc>
bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return(!(lhs > rhs));
}

template <typename T, typename Alloc>
bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return(!(lhs < rhs));
}

template <typename T, typename Alloc>
void	swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}
}

#endif
