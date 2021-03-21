#pragma once
using namespace std;

#include "NodeInterface.h"
#include <iostream>

class Node : public NodeInterface
{
private:
	int data;
	int height = 1;

	Node* left = nullptr;
	Node* right = nullptr;

	int getLeftHeight() const;

	int getRightHeight() const;

	int getBalance() const;

	void recalculateHeight();
public:
	Node(int _data) : data(_data) {}
	~Node() {}

	int getData() const { return data; }

	Node* getLeftChild() const { return left; }

	Node* getRightChild() const { return right; }

	int getHeight() { return height; }

	friend class AVL;
};
