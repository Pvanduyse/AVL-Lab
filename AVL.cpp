#include "AVL.h"

/*
 * AVL::rebalance() implementation. AVL::rebalance(Node*) called privately, which then calls
 * Node::updateHeight(), AVL::rotateLeft(Node*) and AVL::rotateRight(Node*) recursively as needed.
 */

void AVL::rebalance(Node* &_this_node)
{
	if(_this_node->getBalance() > 1) // right heavy
	{
		if(_this_node->right->getBalance() < 0) //right-left heavy
			rotateRight(_this_node->right);
		rotateLeft(_this_node);
	}

	if(_this_node->getBalance() < -1) // left heavy
	{
		if(_this_node->left->getBalance() > 0) //left-right heavy
			rotateLeft(_this_node->left);
		rotateRight(_this_node);
	}
}

void AVL::rotateLeft(Node* &_this_node)
{
	Node* center_node = _this_node->right->left;
	_this_node->right->left = _this_node;
	_this_node = _this_node->right;
	_this_node->left->right = center_node;

	_this_node->left->recalculateHeight();
	_this_node->recalculateHeight();
}

void AVL::rotateRight(Node* &_this_node)
{
	Node* center_node = _this_node->left->right;
	_this_node->left->right = _this_node;
	_this_node = _this_node->left;
	_this_node->right->left = center_node;

	_this_node->right->recalculateHeight();
	_this_node->recalculateHeight();
}

/*
 * AVL::add() implementation. AVL::add(int) called publicly, which calls AVL::add(int, Node*) recursively
 */

bool AVL::add(int _data)
{
	if(root == nullptr)
	{
		root = new Node(_data);
		return true;
	}

	return add(_data, root);
}

bool AVL::add(int _data, Node* &_this_node)
{
	if(_data == _this_node->data)
		return false;

	if(_data < _this_node->data)
	{
		if(_this_node->left != nullptr)
		{
			// recursively call add on its left. If returns true, rebalance this node.
			if(add(_data, _this_node->left))
			{
				_this_node->recalculateHeight();
				rebalance(_this_node);
				return true;
			}
			else
			{
				return false;
			}
		}

		_this_node->left = new Node(_data);
		_this_node->recalculateHeight();
	}
	else
	{
		if(_this_node->right != nullptr)
		{
			// recursively call add on its right. If returns true, rebalance this node.
			if(add(_data, _this_node->right))
			{
				_this_node->recalculateHeight();
				rebalance(_this_node);
				return true;
			}
			else
			{
				return false;
			}
		}

		_this_node->right = new Node(_data);
		_this_node->recalculateHeight();
		}

	return true;
}

/*
 * AVL::remove() implementation. AVL::remove(int) called publicly, which calls AVL::remove(int, Node*)
 * recursively to find the right node, which it removes with a recursive AVL::replaceWithPreceding(Node*,Node*)
 * (if needed) followed by a single AVL::remove(Node*) call
 */

bool AVL::remove(int _data, Node* &_this_node)
{
	if(_this_node == nullptr)
		return false;

	if(_data < _this_node->data)
	{
		if(remove(_data, _this_node->left))
		{
			_this_node->recalculateHeight();
			rebalance(_this_node);
			return true;
		}
		else
		{
			return false;
		}
	}
	if(_data > _this_node->data)
	{
		if(remove(_data, _this_node->right))
		{
			_this_node->recalculateHeight();
			rebalance(_this_node);
			return true;
		}
		else
		{
			return false;
		}
	}

	if(_this_node->right != nullptr && _this_node->left != nullptr)
	{
		replaceWithPreceding(_this_node, _this_node->left);
		_this_node->recalculateHeight();
		rebalance(_this_node);
	}
	else
		remove(_this_node);

	return true;
}

void AVL::remove(Node* &_to_remove)
{
	Node* temp = _to_remove;

	if(_to_remove->left != nullptr)
		_to_remove = _to_remove->left;
	else
		_to_remove = _to_remove->right;

	delete temp;
}

void AVL::replaceWithPreceding(Node* &_to_remove, Node* &_replacement)
{
	if(_replacement->right == nullptr)
	{
		_to_remove->data = _replacement->data;
		remove(_replacement);
	}
	else
	{
		replaceWithPreceding(_to_remove, _replacement->right);
		_replacement->recalculateHeight();
		rebalance(_replacement);
	}
}

void AVL::clear(Node* &_this_node)
{
	if(_this_node == nullptr)
		return;

	clear(_this_node->right);
	clear(_this_node->left);

	delete _this_node;
	_this_node = nullptr;
}
