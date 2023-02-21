#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include "iterator.hpp"
# include "utils.hpp"
namespace ft
{
template <typename Key, typename Val>
struct Node
{
	pair<Key, Val>	_data;
	Node*			_right;
	Node*			_left;

	Node()
		: _data(), _right(NULL), _left(NULL) {}

	Node(pair<Key, T> data)
		: _data(data), _right(NULL), _left(NULL) {}
};

template <typename Key, typename Val,
			typename Alloc = std::allocator<pair<Key, Val> > >
class tree
{
public:
	typedef	Alloc			allocator_type;
	typedef Node<Key, Val>	node_type;
	typedef node_type*		node_ptr;

	tree() : root(NULL) {}
	~tree() {}

private:
	node_ptr		_root;
	node_ptr		_tail;
	allocator_type	_alloc;

	void	InOrder(node_ptr curr)
	{
		if (curr != NULL)
		{
			InOrder(curr->_left);
			InOrder(curr->_right);
		}
	}

	node_ptr	SearchMaxNode(node_ptr	node)
	{
		if (node == NULL)
			return NULL;

		while (node->_right != NULL)
		{
			node = node->_right;
		}
		return (node);
	}

	node_ptr	SearchMinNode(node_ptr	node)
	{
		if (node == NULL)
			return NULL;

		while (node->_left != NULL)
		{
			node = node->_left;
		}
		return (node);
	}

	node_ptr	RemoveSequence(node_ptr node, Key key)
	{
		if (node == NULL)
			return (NULL);

		Key	nodeKey = node->_data->_first;
		if (nodeKey > key)
			node->_left = RemoveSequence(node->_left, key);
		else if (nodeKey < key)
			node->_right = RemoveSequence(node->_right, key);
		else
		{
			node_ptr	ptr = node;

			if (!node->_left && !node->_right)
			{
				delete node;
				node = NULL;
			}
			else if (!node->_left)
			{
				node = node->_right;
				delete ptr;
			}
			else if (!node->_right)
			{
				node = node->_left;
				delete ptr;
			}
			else
			{
				node_ptr	min = SearchMinNode(node->_right);

				node = node->_right;
				delete ptr;
			}
		}
	}
};


}

#endif
