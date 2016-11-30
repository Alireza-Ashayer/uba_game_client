#include "LoginScene.h"
#include "ui_wrappers/LabelWrapper.h"

USING_NS_CC;
USING_NS_CC_UI;
USING_NS_UBA;

Scene* LoginScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = LoginScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoginScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    

	if (!createUI())
		return false;
	


    return true;
}

bool LoginScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("textures/background.jpg");
	if (background)
	{
		background->setPosition(visibleSize / 2);
		addChild(background);
	}


	auto signupLabel = LabelWrapper::createByKey("LOGIN", 36);
	if (signupLabel)
	{
		signupLabel->setPosition(visibleSize / 2 + Size(0, 250));
		signupLabel->setTextColor(Color4B::BLACK);
		addChild(signupLabel);
	}


	//create text boxes
	for (unsigned int i = 0; i < 2; ++i)
	{
		std::string placeHolderKey;

		switch (i)
		{
		case 0:
			placeHolderKey = "YOUR_EMAIL";
			break;
		case 1:
			placeHolderKey = "PASSWORD";
			break;
		}


		int offsetY = (-(int)i) * 60;

		auto textbox = TextBoxWrapper::createByKey(placeHolderKey, 24);
		if (textbox)
		{
			textbox->setName(placeHolderKey);
			textbox->setPosition(visibleSize / 2 + Size(0, 150 + offsetY));
			textbox->setMaxLength(24);
			textbox->setMaxLengthEnabled(true);
			textbox->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));
			addChild(textbox);


			if (i == 1)
			{
				textbox->setPasswordEnabled(true);
			}
		}
	}


	//login button
	auto loginButton = ButtonWrapper::createByKey("LOGIN", 24);
	if (loginButton)
	{
		loginButton->setName("login_button");
		loginButton->addTouchEventListener(CC_CALLBACK_2(LoginScene::buttonCallback, this));
		loginButton->setPosition(visibleSize / 2 + Size(100, -250));
		addChild(loginButton);
	}


	//cancel button
	auto cancelButton = ButtonWrapper::createByKey("CANCEL", 24);
	if (cancelButton)
	{
		cancelButton->setName("cancel_button");
		cancelButton->addTouchEventListener(CC_CALLBACK_2(LoginScene::buttonCallback, this));
		cancelButton->setPosition(visibleSize / 2 + Size(-100, -250));
		addChild(cancelButton);
	}


	return true;
}

void uba::LoginScene::textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type)
{
	//this callback will be used for analytics
	auto node = static_cast<cocos2d::Node*>(pSender);
	auto name = node->getName();

	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		node->setColor(Color3B::RED);
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		node->setColor(Color3B::WHITE);
		break;
	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
		break;
	default:
		break;
	}

}


void uba::LoginScene::buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type)
{
	if (type == Button::TouchEventType::ENDED)
	{
		auto button = static_cast<ButtonWrapper*>(pSender);
		auto name = button->getName();

		if (name == "login_button")
		{
			//TODO
		}
		else if (name == "cancel_button")
		{
			Director::getInstance()->popScene();
		}
	}
}
