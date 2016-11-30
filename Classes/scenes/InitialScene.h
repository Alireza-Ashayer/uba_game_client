#ifndef InitialScene_h__
#define InitialScene_h__


#include "cocos2d.h"

#include "macros/AppMacros.h"
#include "ui_wrappers/ButtonWrapper.h"

NS_UBA_BEGIN

class InitialScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

private:
	CREATE_FUNC(InitialScene);

    bool init() override;
    
	bool createUI();

	void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type);
};

NS_UBA_END

#endif // InitialScene_h__
