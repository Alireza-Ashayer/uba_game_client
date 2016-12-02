#include "Entity.h"


USING_NS_UBA;

const int Entity::BLOCK_SIZE = 64;

bool Entity::init(int index)
{
	if (!Node::init())
		return false;

	_index = index;

	setPositionX(index * BLOCK_SIZE);
	setPositionY(0);

	setContentSize(cocos2d::Size(BLOCK_SIZE, BLOCK_SIZE));

	return true;
}

void uba::Entity::moveToFront(int maxScreenEntities)
{
	setPositionX(_position.x + maxScreenEntities * BLOCK_SIZE);
}
