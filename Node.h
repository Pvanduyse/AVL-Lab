#pragma once

using namespace std;

#include "NodeInterface.h"

class Node : public NodeInterface
{
private:
	int data;
	int height = 1;

	Node* left_child = nullptr;
	Node* right_child = nullptr;

	int getHeight(const Node* _child) const;

	int getBalance() const;
	void recalcHeight();
public:
	Node(int _data) : data(_data) {}
	~Node() {}

	int getData() const { return data; }

	Node* getLeftChild() const { return left_child; }
	Node* getRightChild() const { return right_child; }

	int getHeight() { return height; }

	friend class AVL;
};
