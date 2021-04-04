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

	static int getHeight(const Node* _this_node);
	void recalcHeight();

	void rebalance();
	void rotateLeft();
	void rotateRight();

	static void remove(Node*& _this_node);
	void replaceWithRightmostOf(Node* &_to_remove);
public:
	Node(int _data) : data(_data) {}
	~Node();

	bool add(const int &data);

	int remove(const int &_data); // -1 if node deleted, 0 if not found, 1 if removed

	int getData() const { return data; }

	Node* getLeftChild() const { return left_child; }
	Node* getRightChild() const { return right_child; }

	int getHeight() { return height; }
};
