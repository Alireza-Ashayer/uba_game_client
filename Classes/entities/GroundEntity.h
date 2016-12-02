#ifndef GroundEntity_h__
#define GroundEntity_h__


#include "entities/Entity.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class GroundEntity : public Entity
{
public:
	static GroundEntity* create(int index);


	bool isHazard() override;
	bool hasCollision() override;
	bool isStatic() override;
	bool removeOnExit() override;

private:
	bool init(int index);
	

};

NS_UBA_END

#endif // GroundEntity_h__
