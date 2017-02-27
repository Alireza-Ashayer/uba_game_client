#include "PlayerEntity.h"

#include "2d/CCSprite.h"

#include "entities/HazardEntity.h"

USING_NS_UBA;


PlayerEntity* uba::PlayerEntity::create(int index)
{
	auto* obj = new (std::nothrow) PlayerEntity;
	if (obj && obj->init(index))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}



bool PlayerEntity::init(int index)
{
	if (!Entity::init(index))
		return false;

	_sprite = cocos2d::Sprite::create("textures/player/player_walk_0.png");
	if (_sprite)
	{
		_sprite->setPosition(_contentSize / 2 + cocos2d::Size(0, -5));
		addChild(_sprite);
	}

	setPositionY(BLOCK_SIZE);

	_slideTimer = -1;
	_vy = 0;
	_playerState = PlayerState::WALK;

	scheduleUpdate();

	return true;
}

bool uba::PlayerEntity::isHazard()
{
	return false;
}

bool uba::PlayerEntity::hasCollision()
{
	return false;
}

bool uba::PlayerEntity::isStatic()
{
	return true;
}

void uba::PlayerEntity::update(float dt)
{
	Entity::update(dt);

	if (_playerState == PlayerState::JUMP)
	{
		_vy -= 0.2f;
		setPositionY(_position.y + _vy);
		
		if (_position.y < BLOCK_SIZE)
		{
			_playerState = PlayerState::WALK;
			_vy = 0;
		}
	}
	else if (_playerState == PlayerState::SLIDE)
	{
		if (_slideTimer == -1)
		{
			if (_scaleY > 0.5f)
			{
				setScaleY(_scaleY - 0.05);
				if (_scaleY < 0.5f)
				{
					_slideTimer = 0;
				}
			}
		}
		else if (_slideTimer == -2)
		{
			if (_scaleY < 1.0f)
			{
				setScaleY(_scaleY + 0.05);
				if (_scaleY >= 1.0f)
				{
					_slideTimer = -1;
					_playerState = PlayerState::WALK;
				}
			}
		}
		else if (_slideTimer >= 0.0f)
		{
			_slideTimer += dt;
			if (_slideTimer >= 0.5f)
			{
				_slideTimer = -2;
			}
		}
	}
}

void uba::PlayerEntity::switchPlayerState(PlayerState newState)
{
	if (_playerState == PlayerState::WALK)
	{
		_playerState = newState;

		switch (newState)
		{
		case uba::PlayerState::WALK:
			_currentAnimationIndex = 0;
			_maxAnimationIndex = 8;
			break;
		case uba::PlayerState::JUMP:
			_currentAnimationIndex = 0;
			_maxAnimationIndex = 2;
			_vy = 5;
			break;
		case uba::PlayerState::SLIDE:
			_slideTimer = -1;
			break;
		default:
			break;
		}
	}
}

bool uba::PlayerEntity::removeOnExit()
{
	return false;
}

bool uba::PlayerEntity::collidesWith(Entity* entity)
{
	auto hazard = static_cast<HazardEntity*>(entity);

	auto hazardBB = hazard->getPosition();
	
	if (_position.x > hazardBB.x + 5 && _position.x < hazardBB.x + BLOCK_SIZE - 5)
	{
		if (_playerState == PlayerState::JUMP && hazard->getHazardType() == HazardType::JUMP)
		{
			return false;
		}
		else if (_playerState == PlayerState::SLIDE && hazard->getHazardType() == HazardType::SLIDE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;
}
