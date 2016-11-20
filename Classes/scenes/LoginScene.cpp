#include "LoginScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_UBA;
USING_NS_CC_UI;

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


	return true;
}


