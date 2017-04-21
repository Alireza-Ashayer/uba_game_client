#include "HazardEntity.h"

#include "2d/CCSprite.h"
#include "base/ccRandom.h"

USING_NS_UBA;


HazardEntity* uba::HazardEntity::create(int index)
{
	auto* obj = new (std::nothrow) HazardEntity;
	if (obj && obj->init(index))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}



bool HazardEntity::init(int index)
{
	if (!Entity::init(index))
		return false;

	auto sprite = cocos2d::Sprite::create("textures/level_hazard.png");
	if (sprite)
	{
		sprite->setPosition(_contentSize / 2);
		addChild(sprite);
	}


	auto r = cocos2d::RandomHelper::random_int(0, 2);

	if (r == 0)
	{
		//for jump
		setPositionY(BLOCK_SIZE);
		_hazardType = HazardType::JUMP;
	}
	else if (r == 1)
	{
		//for slide
		setPositionY(1.4f * BLOCK_SIZE);
		_hazardType = HazardType::SLIDE;
	}
	else
	{
		return false;
		//ignore do not add
	}

	return true;
}

bool uba::HazardEntity::isHazard()
{
	return true;
}

bool uba::HazardEntity::hasCollision()
{
	return true;
}

bool uba::HazardEntity::isStatic()
{
	return false;
}

void uba::HazardEntity::moveToFront(int maxScreenEntities)
{
}

bool uba::HazardEntity::removeOnExit()
{
	return true;
}
