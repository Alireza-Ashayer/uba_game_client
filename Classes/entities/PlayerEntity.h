#ifndef PlayerEntity_h__
#define PlayerEntity_h__


#include "2d/CCSprite.h"
#include "entities/Entity.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

enum class PlayerState
{
	WALK,
	JUMP,
	SLIDE
};


class PlayerEntity : public Entity
{
public:
	static PlayerEntity* create(int index);


	bool isHazard() override;
	bool hasCollision() override;
	bool isStatic() override;
	bool removeOnExit() override;

	void switchPlayerState(PlayerState newState);

	bool collidesWith(Entity* entity);
private:
	bool init(int index);
	void update(float dt) override;

	PlayerState _playerState;

	cocos2d::Sprite* _sprite;

	int _currentAnimationIndex;
	int _maxAnimationIndex;

	float _vy;
	float _slideTimer;

};

NS_UBA_END

#endif // PlayerEntity_h__
