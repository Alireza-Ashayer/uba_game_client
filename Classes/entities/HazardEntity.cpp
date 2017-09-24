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

	auto r = cocos2d::RandomHelper::random_int(0, 1);

	if (r == 0)
	{
		//for jump
		_hazardType = HazardType::JUMP;

		auto sprite = cocos2d::Sprite::create("textures/level_hazard.png");
		if (sprite)
		{
			sprite->setPosition(_contentSize / 2 + cocos2d::Size(0, 0.7 * BLOCK_SIZE));
			addChild(sprite);
		}
	}
	else if (r == 1)
	{
		//for slide
		_hazardType = HazardType::SLIDE;

		for (unsigned int i = 1; i <= 20; ++i)
		{
			auto sprite = cocos2d::Sprite::create("textures/level_hazard.png");
			if (sprite)
			{
				sprite->setPosition(_contentSize / 2 + cocos2d::Size(0, BLOCK_SIZE / 2 + (1.1f * BLOCK_SIZE / 2)* i));
				addChild(sprite);
			}

		}
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
