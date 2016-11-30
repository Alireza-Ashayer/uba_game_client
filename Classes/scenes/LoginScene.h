#ifndef LoginScene_h__
#define LoginScene_h__


#include "cocos2d.h"

#include "macros/AppMacros.h"
#include "ui_wrappers/TextBoxWrapper.h"
#include "ui_wrappers/ButtonWrapper.h"

NS_UBA_BEGIN

class LoginScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

private:
	CREATE_FUNC(LoginScene);

    bool init() override;
    
	bool createUI();

	void textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type);
	void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type);
};

NS_UBA_END

#endif // LoginScene_h__
