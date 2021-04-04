#pragma once

using namespace std;

#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface
{
private:
	Node* root = nullptr;
public:
	AVL() {}
	~AVL() { clear(); }

	Node* getRootNode() const { return root; }

	bool add(int _data)
	{
		if(root == nullptr)
		{
			root = new Node(_data);
			return true;
		}

		return root->add(_data);
	}

	bool remove(int _data)
	{
		if(root == nullptr)
			return false;

		switch(root->remove(_data))
		{
		case -1:
			root = nullptr;

		case 1:
			return 1;
		}

		return 0;
	}

	void clear() { delete root;root = nullptr; }
};
