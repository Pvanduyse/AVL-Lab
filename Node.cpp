#include "Node.h"

int Node::getHeight(const Node* _child) const
{
	return (_child != nullptr) ? _child->height : 0;
}

int Node::getBalance() const
{
	return getHeight(right_child) - getHeight(left_child);
}

void Node::recalcHeight()
{
	if(getHeight(left_child) > getHeight(right_child))
		height = getHeight(left_child) + 1;
	else
		height = getHeight(right_child) + 1;
}
