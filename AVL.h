#pragma once

using namespace std;

#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface
{
private:
	int DEBUG_ADD = 0;
	int DEBUG_REMOVE = 0;
	int DEBUG_REBALANCE = 0;
	int DEBUG_REBALANCE_ACTIVE = 0;
	Node* root = nullptr;

	void rebalance(Node* &_this_node);

	void rotateLeft(Node* &_this_node);

	void rotateRight(Node* &_this_node);

	bool add(int _data, Node* &_this_node);

	bool remove(int _data, Node* &_this_node);

	void remove(Node* &_to_remove);

	void replaceWithPreceding(Node* &_to_remove, Node* &_replacement);

	void clear(Node* &_this_node);
public:
	AVL() {}
	~AVL() { clear(); }

	bool add(int _data);

	Node* getRootNode() const { return root; }

	bool remove(int _data) { return remove(_data, root); }

	void clear() { clear(root); }
};
