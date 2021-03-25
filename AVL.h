#pragma once

using namespace std;

#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface
{
private:
	Node* root = nullptr;

	void rebalance(Node* &_local_root);
	void rotateLeft(Node* &_local_root);
	void rotateRight(Node* &_local_root);

	bool add(const int &_data, Node* &_local_root);

	bool remove(const int &_data, Node* &_local_root);
	void replaceWithPreceding(Node* &_to_replace, Node* &_to_remove);

	void clear(Node* &_local_root);
public:
	AVL() {}
	~AVL() { clear(); }

	Node* getRootNode() const { return root; }

	bool add(int _data) { return add(_data, root); }

	bool remove(int _data) { return remove(_data, root); }

	void clear() { clear(root); }
};
