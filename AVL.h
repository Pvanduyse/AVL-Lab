#pragma once

using namespace std;

#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface
{
private:
	Node* root;
public:
	AVL() {}
	~AVL() { clear(); }

	Node* getRootNode() const { return root; }

	bool add(int _data) { return false; }

	bool remove(int _data) { return false; }

	void clear() {}
};
