#ifndef LoginScene_h__
#define LoginScene_h__


#include "cocos2d.h"

#include "macros/AppMacros.h"
#include "ui/UITextField.h"

NS_UBA_BEGIN

class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

private:
	CREATE_FUNC(LoginScene);

    bool init() override;
    
	bool createUI();

	void textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type);

};

NS_UBA_END

#endif // LoginScene_h__
