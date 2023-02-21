#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "iterator.hpp"
# include "utils.hpp"

#include <map>

namespace ft
{
template <typename Key, typename T, typename Compare = ft::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef implementation-defined						iterator;
	typedef implementation-defined						const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	class value_compare
	{
			friend class map;
		protected:
			key_compare _comp;

			value_compare(key_compare c) : _comp(c) {}
		public:
			bool	operator()(const value_type& x, const value_type& y) const
			{ return (_comp(x.first, y.first)); }
	}

	private:


	/* Constructor */

	explicit map(const Compare& comp, const Alloc& alloc = Alloc());
	template <typename Iter>
	map(Iter first, Iter last, const Compare& comp, const Alloc& alloc = Alloc());
	map(const map& copy);

	/* Destructor */

	~map();

	/* Assign operator */

	map&	operator=(const map& copy);

	/* Element access */

	T&			at(const Key& key);
	const T&	at(const Key& key) const;

	T&			operator[](const Key& key);

	/* Iterator */

	iterator				begin();
	iterator				end();
	const_iterator			begin() const;
	const_iterator			end() const;

	reverse_iterator		rbegin();
	reverse_iterator		end();
	const_reverse_iterator	rbegin() const;
	const_reverse_iterator	end() const;

	/* Capacity */

	bool		empty();
	size_type	size();
	size_type	max_size() const;

	/* Modifiers */

	void						clear();
	ft::pair<iterator, bool>	insert(const value_type& value);
	iterator					insert(iterator pos, const value_type& value);
	template <typename Iter>
	void						insert(Iter first, Iter last);
	iterator					erase(iterator pos);
	iterator					erase(iterator first, iterator last);
	iterator					erase(const Key& key);
	void						swap(map& other);

	/* Lookup */

	size_type									count(const Key& key) const;
	iterator									find(const Key& key);
	const_iterator								find(const Key& key) const;
	ft::pair<iterator, iterator>				equal_range(const Key& key);
	ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const;
	iterator									lower_bound(const Key& key);
	const_iterator								lower_bound(const Key& key) const;
	iterator									upper_bound(const Key& key);
	const_iterator								upper_bound(const Key& key) const;

	/* Observes */

	key_compare		key_comp() const;
	value_compare	value_comp() const;
};

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
					const ft::map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
					const ft::map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
					const ft::map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
					const ft::map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
					const ft::map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
					const ft::map<Key, T, Compare, Alloc>& rhs);


template <typename Key, typename T, typename Compare, typename Alloc>
void	swap(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs);

}

#endif
