#pragma once
using namespace std;

#include "Node.h"

class Node : public NodeInterface
{
private:
	int data;
	int height;

	Node* leftChild = NULL;
	Node* rightChild = NULL;
public:
	Node(int _data)
	{
		data = _data;
		height = 1;
	}
	~Node() {}

	int getData() const { return data; }

	Node* getLeftChild() const { return leftChild; }

	Node* getRightChild() const { return rightChild; }

	int getHeight() { return height; }

	friend class AVL;
};
