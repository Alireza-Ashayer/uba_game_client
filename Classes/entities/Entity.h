#ifndef Entity_h__
#define Entity_h__

#include "2d/CCNode.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class Entity : public cocos2d::Node
{
public:
	const static int BLOCK_SIZE;
	
	virtual void moveToFront(int maxScreenEntities);

	virtual bool isHazard() = 0;
	virtual bool isStatic() = 0;
	virtual bool hasCollision() = 0;
	virtual bool removeOnExit() = 0;

	int getIndex() const { return _index; }
protected:
	bool init(int index);


	int _index;
};

NS_UBA_END

#endif // Entity_h__
