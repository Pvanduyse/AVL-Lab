#include "AVL.h"

/*
 * AVL::rebalance() implementation. AVL::rebalance(Node*) called privately, which then calls
 * AVL::rotateLeft(Node*) and AVL::rotateRight(Node*) as needed.
 */
void AVL::rebalance(Node* &_local_root)
{
	// Recalculate _local_root's height
	// make sure that any nodes not being checked for rebalancing call this directly
	_local_root->recalcHeight();

	// If the upper (right) half of this local tree is heavyier, rotate the tree to the left
	if(_local_root->getBalance() > 1)
	{
		// If the right half of tree is skewed inward, rotate it out first to avoid repetitive rotation
		if(_local_root->right_child->getBalance() < 0)
			rotateRight(_local_root->right_child);

		rotateLeft(_local_root);
	}

	// If the lower (left) half of this local tree is heavyier, rotate the tree to the right
	if(_local_root->getBalance() < -1)
	{
		// If the left half of tree is skewed inward, rotate it out first to avoid repetitive rotation
		if(_local_root->left_child->getBalance() > 0)
			rotateLeft(_local_root->left_child);

		rotateRight(_local_root);
	}
}

void AVL::rotateLeft(Node* &_local_root)
{
	// One of the new_root's nodes is going to get swapped around. Save it in the meantime.
	Node* center_node = _local_root->right_child->left_child;

	// Re-hook up the old root, new root, and center node
	_local_root->right_child->left_child = _local_root;
	_local_root = _local_root->right_child;
	_local_root->left_child->right_child = center_node;

	// Recalculate both the old and new roots' heights
	_local_root->left_child->recalcHeight();
	_local_root->recalcHeight();
}

void AVL::rotateRight(Node* &_local_root)
{
	// One of the new_root's nodes is going to get swapped around. Save it in the meantime.
	Node* center_node = _local_root->left_child->right_child;

	// Re-hook up the old root, new root, and center node
	_local_root->left_child->right_child = _local_root;
	_local_root = _local_root->left_child;
	_local_root->right_child->left_child = center_node;

	// Recalculate both the old and new roots' heights
	_local_root->right_child->recalcHeight();
	_local_root->recalcHeight();
}

/*
 * AVL::add() implementation. AVL::add(int) called publicly, which calls AVL::add(int, Node*) recursively
 */
bool AVL::add(const int &_data, Node* &_local_root)
{
	// End condition - value not found, adding
	if(_local_root == nullptr)
	{
		_local_root = new Node(_data);
		return true;
	}

	// End condition - duplicate value
	if(_data == _local_root->data)
		return false;

	// Recursive return. Calls rebalance(_local_root) if returning true
	if(add(_data, (_data < _local_root->data) ? _local_root->left_child : _local_root->right_child))
	{
		rebalance(_local_root);
		return true;
	}

	return false;
}

/*
 * AVL::remove() implementation. AVL::remove(int) called publicly, which calls AVL::remove(int, Node*)
 * recursively to find the right node, which if found is removed with a recursive
 * AVL::replaceWithPreceding(Node*,Node*) (if needed) followed by a single AVL::remove(Node*) call
 */
bool AVL::remove(const int &_data, Node* &_local_root)
{
	// End condition - value not found
	if(_local_root == nullptr)
		return false;

	// End condition - value found, removing
	if(_data == _local_root->data)
	{
		if((_local_root->right_child != nullptr) && (_local_root->left_child != nullptr))
		{ // This deals with nodes that have two child nodes
			replaceWithPreceding(_local_root, _local_root->left_child);
			rebalance(_local_root);
		}
		else
		{ // This deals with nodes that have at most one child nodes, just save, relink, and delete
			Node* temp = _local_root;
			_local_root = (_local_root->left_child != nullptr) ? _local_root->left_child : _local_root->right_child;
			delete temp;
		}

		return true;
	}

	// Recursion called with right or left child as determined by an inline conditional
	if(remove(_data, (_data < _local_root->data) ? _local_root->left_child : _local_root->right_child))
	{
		rebalance(_local_root);
		return true;
	}

	return false;
}

void AVL::replaceWithPreceding(Node* &_to_replace, Node* &_to_remove)
{
	// End condition - _to_remove holds the value immediately preceding _to_replace
	if(_to_remove->right_child == nullptr)
	{
		// Transfer data and remove the now redundant node
		_to_replace->data = _to_remove->data;
		Node* temp = _to_remove;
		_to_remove = _to_remove->left_child;
		delete temp;
		return;
	}

	// Recursion
	replaceWithPreceding(_to_replace, _to_remove->right_child);
	rebalance(_to_remove);
}

void AVL::clear(Node* &_local_root)
{
	// End condition
	if(_local_root == nullptr)
		return;

	// Recursion
	clear(_local_root->right_child);
	clear(_local_root->left_child);

	// Deletion
	delete _local_root;
	_local_root = nullptr;
}
