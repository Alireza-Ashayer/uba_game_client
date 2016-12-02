#ifndef HazardEntity_h__
#define HazardEntity_h__

#include "entities/Entity.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

enum class HazardType
{
	JUMP,
	SLIDE
};

class HazardEntity : public Entity
{
public:
	static HazardEntity* create(int index);


	bool isHazard() override;
	bool hasCollision() override;
	bool isStatic() override;
	bool removeOnExit() override;

	void moveToFront(int maxScreenEntities) override;

	uba::HazardType getHazardType() const { return _hazardType; }
private:
	bool init(int index);
	
	HazardType _hazardType;
};

NS_UBA_END

#endif // HazardEntity_h__
