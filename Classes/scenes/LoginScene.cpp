#include "LoginScene.h"
#include "ui_wrappers/LabelWrapper.h"
#include "ui_wrappers/TextBoxWrapper.h"

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
    if (!Layer::init())
        return false;
    

	if (!createUI())
		return false;
	


    return true;
}

bool LoginScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto welcomeLabel = LabelWrapper::createByKey("WELCOME", 48);
	if (welcomeLabel)
	{
		welcomeLabel->setPosition(visibleSize / 2 + Size(0, 200));
		addChild(welcomeLabel);
	}

	auto usernameLabel = LabelWrapper::createByKey("USERNAME", 32);
	if (usernameLabel)
	{
		usernameLabel->setPosition(visibleSize / 2 + Size(0, 100));
		addChild(usernameLabel);
	}

	auto usernameTextbox = TextBoxWrapper::createByKey("USERNAME_PLACEHOLDER", 24);
	if (usernameTextbox)
	{
		usernameTextbox->setName("username_tb");
		usernameTextbox->setPosition(visibleSize / 2 + Size(0, 60));
		usernameTextbox->setMaxLength(24);
		usernameTextbox->setMaxLengthEnabled(true);
		usernameTextbox->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));
		addChild(usernameTextbox);
	}


	auto passwordLabel = LabelWrapper::createByKey("PASSWORD", 32);
	if (passwordLabel)
	{
		passwordLabel->setPosition(visibleSize / 2 + Size(0, -50));
		addChild(passwordLabel);
	}

	auto passwordTextbox = TextBoxWrapper::createByKey("PASSWORD_PLACEHOLDER", 24);
	if (passwordTextbox)
	{
		usernameTextbox->setName("password_tb");
		passwordTextbox->setPosition(visibleSize / 2 + Size(0, -90));
		passwordTextbox->setMaxLength(24);
		passwordTextbox->setMaxLengthEnabled(true);
		passwordTextbox->setPasswordEnabled(true);
		passwordTextbox->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));
		addChild(passwordTextbox);
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


