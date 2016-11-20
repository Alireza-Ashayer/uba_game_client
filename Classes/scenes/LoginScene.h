#ifndef LoginScene_h__
#define LoginScene_h__


#include "cocos2d.h"

#include "macros/AppMacros.h"

NS_UBA_BEGIN

class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

private:
	CREATE_FUNC(LoginScene);

    bool init() override;
    
	bool createUI();

};

NS_UBA_END

#endif // LoginScene_h__
