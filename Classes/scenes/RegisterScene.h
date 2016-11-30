#ifndef RegisterScene_h__
#define RegisterScene_h__


#include "cocos2d.h"

#include "macros/AppMacros.h"
#include "ui_wrappers/TextBoxWrapper.h"
#include "ui_wrappers/CheckBoxWrapper.h"
#include "ui_wrappers/ButtonWrapper.h"

NS_UBA_BEGIN

class RegisterScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

private:
	CREATE_FUNC(RegisterScene);

    bool init() override;
    
	bool createUI();

	void textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type);
	void checkBoxEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type);
};

NS_UBA_END

#endif // RegisterScene_h__
