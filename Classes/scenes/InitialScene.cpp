#include "InitialScene.h"
#include "ui_wrappers/LabelWrapper.h"
#include "LoginScene.h"
#include "RegisterScene.h"

USING_NS_CC;
USING_NS_CC_UI;
USING_NS_UBA;

Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = InitialScene::create();

    scene->addChild(layer);

    return scene;
}

bool InitialScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    

	if (!createUI())
		return false;
	


    return true;
}

bool InitialScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("textures/background.jpg");
	if (background)
	{
		background->setPosition(visibleSize / 2);
		addChild(background);
	}


	auto welcomeLabel = LabelWrapper::createByKey("WELCOME", 36);
	if (welcomeLabel)
	{
		welcomeLabel->setPosition(visibleSize / 2 + Size(0, 250));
		welcomeLabel->setTextColor(Color4B::BLACK);
		addChild(welcomeLabel);
	}


	//register button
	auto registerButton = ButtonWrapper::createByKey("REGISTER", 24);
	if (registerButton)
	{
		registerButton->setName("register_button");
		registerButton->addTouchEventListener(CC_CALLBACK_2(InitialScene::buttonCallback, this));
		registerButton->setPosition(visibleSize / 2 + Size(-100, -50));
		addChild(registerButton);
	}



	//login button
	auto loginButton = ButtonWrapper::createByKey("LOGIN", 24);
	if (loginButton)
	{
		loginButton->setName("login_button");
		loginButton->addTouchEventListener(CC_CALLBACK_2(InitialScene::buttonCallback, this));
		loginButton->setPosition(visibleSize / 2 + Size(100, -50));
		addChild(loginButton);
	}

	return true;
}


void uba::InitialScene::buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type)
{
	if (type == ui::Button::TouchEventType::ENDED)
	{
		auto button = static_cast<ButtonWrapper*>(pSender);
		auto name = button->getName();

		if (name == "login_button")
		{
			auto scene = LoginScene::createScene();
			if (scene)
			{
				Director::getInstance()->pushScene(scene);
			}
		}
		else if (name == "register_button")
		{
			auto scene = RegisterScene::createScene();
			if (scene)
			{
				Director::getInstance()->pushScene(scene);
			}
		}
	}
}
