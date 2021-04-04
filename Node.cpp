#include "Node.h"
#include <iostream>

Node::~Node()
{
	if(left_child != nullptr)
		delete left_child;

	if(right_child != nullptr)
		delete right_child;
}

int Node::getHeight(const Node* _this_node)
{
	return (_this_node != nullptr) ? _this_node->height : 0;
}

void Node::recalcHeight()
{
	height = 1 + ((getHeight(left_child) > getHeight(right_child)) ? getHeight(left_child) : getHeight(right_child));
}

void Node::rebalance()
{
	// Recalculate _local_root's height
	// make sure that any nodes not being checked for rebalancing call this directly
	recalcHeight();

	// If the upper (right) half of this local tree is heavyier, rotate the tree to the left
	if(getHeight(right_child)-1 > getHeight(left_child))
	{
		// If the right half of tree is skewed inward, rotate it out first to avoid repetitive rotation
		if(getHeight(right_child->left_child) > getHeight(right_child->right_child))
			right_child->rotateRight();

		rotateLeft();
	}

	// If the lower (left) half of this local tree is heavyier, rotate the tree to the right
	if(getHeight(left_child)-1 > getHeight(right_child))
	{
		// If the left half of tree is skewed inward, rotate it out first to avoid repetitive rotation
		if(getHeight(left_child->right_child) > getHeight(left_child->left_child))
			left_child->rotateLeft();

		rotateRight();
	}
}

void Node::rotateLeft()
{
	int temp = data;
	data = right_child->data;
	right_child->data = temp;

	// One of the new_root's nodes is going to get swapped around. Save it in the meantime.
	Node* trade = right_child;

	// Re-hook up the old root, new root, and center node
	right_child = right_child->right_child;
	trade->right_child = trade->left_child;
	trade->left_child = left_child;
	left_child = trade;

	// Recalculate both the old and new roots' heights
	left_child->recalcHeight();
	recalcHeight();
}

void Node::rotateRight()
{
	int temp = data;
	data = left_child->data;
	left_child->data = temp;


	// One of the new_root's nodes is going to get swapped around. Save it in the meantime.
	Node* trade = left_child;

	// Re-hook up the old root, new root, and center node
	left_child = left_child->left_child;
	trade->left_child = trade->right_child;
	trade->right_child = right_child;
	right_child = trade;

	// Recalculate both the old and new roots' heights
	right_child->recalcHeight();
	recalcHeight();
}

bool Node::add(const int &_data)
{
	// End condition - duplicate value
	if(_data == data)
		return false;

	Node*& next_node = (_data < data) ? left_child : right_child;

	// End condition - value not found, adding
	if(next_node == nullptr)
	{
		next_node = new Node(_data);
		recalcHeight();
		return true;
	}

	// Recursive return. Calls rebalance() if returning true
	if(next_node->add(_data))
	{
		rebalance();
		return true;
	}
	return false;
}

int Node::remove(const int &_data)
{
	// End condition - value found, removing
	if(data == _data)
	{
		if(height == 1)
		{ // This deals with nodes that have no child nodes
			Node* to_remove = this;
			remove(to_remove);
			return -1;
		}

		if((right_child != nullptr) && (left_child != nullptr))
		{ // This deals with nodes that have two child nodes
			replaceWithRightmostOf(left_child);
			rebalance();
		}
		else
		{ // This deals with nodes that have only one child node: just save, replace, and delete
			Node* replacement = (left_child != nullptr) ? left_child : right_child;
			*this = *replacement;
			remove(replacement);
			rebalance();
		}
		return 1;
	}

	Node*& next_node = (data > _data) ? left_child : right_child;

	if(next_node == nullptr)
		return 0;

	// Recursion called with right or left child as determined by an inline conditional
	switch(next_node->remove(_data))
	{
		case 0:
			return 0;
		case -1:
			next_node = nullptr;
		default:
			rebalance();
			return 1;
	}
}

void Node::remove(Node*& _this_node)
{
	if(_this_node->height == 1)
	{
		delete _this_node;
		_this_node = nullptr;
		return;
	}

	Node* replacement = (_this_node->right_child != nullptr) ? _this_node->right_child : _this_node->left_child;
	*_this_node = *replacement;
	replacement->right_child = nullptr;
	replacement->left_child = nullptr;
	delete replacement;
}

void Node::replaceWithRightmostOf(Node* &_to_remove)
{
	// End condition - _to_remove holds the value immediately preceding this node
	if(_to_remove->right_child == nullptr)
	{
		data = _to_remove->data;
		remove(_to_remove);
		return;
	}

	// Recursion
	replaceWithRightmostOf(_to_remove->right_child);
	_to_remove->rebalance();
}
