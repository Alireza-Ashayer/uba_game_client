#include "GroundEntity.h"

#include "2d/CCSprite.h"

USING_NS_UBA;


GroundEntity* uba::GroundEntity::create(int index)
{
	auto* obj = new (std::nothrow) GroundEntity;
	if (obj && obj->init(index))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}



bool GroundEntity::init(int index)
{
	if (!Entity::init(index))
		return false;

	auto sprite = cocos2d::Sprite::create("textures/level_ground.png");
	if (sprite)
	{
		sprite->setPosition(_contentSize / 2);
		addChild(sprite);
	}



	return true;
}

bool uba::GroundEntity::isHazard()
{
	return false;
}

bool uba::GroundEntity::hasCollision()
{
	return true;
}

bool uba::GroundEntity::isStatic()
{
	return false;
}

bool uba::GroundEntity::removeOnExit()
{
	return false;
}
