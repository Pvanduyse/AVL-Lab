#include "Node.h"

int Node::getLeftHeight() const
{
	return (left != nullptr) ? left->height : 0;
}

int Node::getRightHeight() const
{
	return (right != nullptr) ? right->height : 0;
}

int Node::getBalance() const
{
	return getRightHeight() - getLeftHeight();
}

void Node::recalculateHeight()
{
	if(getLeftHeight() > getRightHeight())
		height = getLeftHeight() + 1;
	else
		height = getRightHeight() + 1;
}
