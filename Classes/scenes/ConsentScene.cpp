#include "ConsentScene.h"
#include "ui_wrappers/LabelWrapper.h"
#include "LoginScene.h"
#include "RegisterScene.h"
#include "GameScene.h"
#include "singletons/StringCache.h"
#include "singletons/User.h"
#include "InitialScene.h"

USING_NS_CC;
USING_NS_CC_UI;
USING_NS_UBA;

Scene* ConsentScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = ConsentScene::create();

    scene->addChild(layer);

    return scene;
}

bool ConsentScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    

	if (!createUI())
		return false;
	


    return true;
}

bool ConsentScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("textures/background.jpg");
	if (background)
	{
		background->setPosition(visibleSize / 2);
		addChild(background);
	}


	auto consentParagraph = LabelWrapper::createByKey("CONSENT", 14);
	if (consentParagraph)
	{
		consentParagraph->setPosition(visibleSize / 2 + Size(0, 20));
		consentParagraph->setTextColor(Color4B::BLACK);
		consentParagraph->setTextAreaSize(Size(visibleSize.width - 20, 0));
		addChild(consentParagraph);
	}






	//play button
	auto acceptButton = ButtonWrapper::createByKey("ACCEPT", 24);
	if (acceptButton)
	{
		acceptButton->setName("accept_button");
		acceptButton->addTouchEventListener(CC_CALLBACK_2(ConsentScene::buttonCallback, this));
		acceptButton->setPosition(visibleSize / 2 + Size(100, -150));
		addChild(acceptButton);
	}

	auto rejectButton = ButtonWrapper::createByKey("REJECT", 24);
	if (rejectButton)
	{
		rejectButton->setName("reject_button");
		rejectButton->addTouchEventListener(CC_CALLBACK_2(ConsentScene::buttonCallback, this));
		rejectButton->setPosition(visibleSize / 2 + Size(-100, -150));
		addChild(rejectButton);
	}

	return true;
}


void uba::ConsentScene::buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type)
{
	if (type == ui::Button::TouchEventType::ENDED)
	{
		auto button = static_cast<ButtonWrapper*>(pSender);
		auto name = button->getName();

		if (name == "accept_button")
		{
			auto scene = InitialScene::createScene();
			if (scene)
			{
				Director::getInstance()->pushScene(scene);
			}
		}
		else if (name == "reject_button")
		{
			Director::getInstance()->end();
			exit(0);
		}
	}
}
