#ifndef STACK_HPP
# define STACK_HPP

# include "utils.hpp"
# include "vector.hpp"

#include <stack>

namespace ft
{
template<typename T, typename Container = vector<T> > class stack;

template<typename T, typename Container>
class stack {
public:
	typedef	Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;
	typedef typename container_type::size_type			size_type;

protected:
	container_type	c;

public:

	/* Constructor */
	explicit stack(const Container& cont = Container())
		:c(cont) {}
	stack(const stack& copy)
		:c(copy.c) {}

	/* Destructor */
	~stack() {}

	/* Assign operator */
	stack&	operator=(const stack& copy)
	{
		c = copy.c;
	}

	/* Element access */
	reference		top()
	{
		return (c.back());
	}

	const_reference	top() const
	{
		return (c.back());
	}

	/* Capacity */
	bool		empty() const
	{
		return (c.empty());
	}

	size_type	size() const
	{
		return (c.size());
	}

	/* Modifier */
	void	push(const value_type&	value)
	{
		return (c.push_back(value));
	}

	void	pop()
	{
		return (c.pop_back());
	}

	/* Operator overloading*/

	friend	bool	operator==(const ft::stack<T, Container>& lhs,
							const ft::stack<T, Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	friend bool	operator<(const ft::stack<T, Container>& lhs,
							const ft::stack<T, Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
};

template<class T, class Container>
bool	operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (!(lhs == rhs));
}

template<class T, class Container>
bool	operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (!(lhs > rhs));
}

template<class T, class Container>
bool	operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (rhs < lhs);
}

template<class T, class Container>
bool	operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (!(lhs < rhs));
}

}

#endif
