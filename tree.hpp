#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include "iterator.hpp"
# include "utils.hpp"
namespace ft
{
enum Color
{
	Black,
	Red
};
template <typename Key, typename Val>
class Node
{
private:
	pair<Key, Val>	_data;
	Node*			_parent;
	Node*			_right;
	Node*			_left;
	bool			_color = Red;
public:
	Node(Key key, Val val) : _data(key, val), _parent(NULL), _right(NULL), _left(NULL) {}
};
}

#endif
