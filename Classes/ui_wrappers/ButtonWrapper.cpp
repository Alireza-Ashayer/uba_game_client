#include "ButtonWrapper.h"

#include "singletons/StringCache.h"
#include "ui_wrappers/LabelWrapper.h"

USING_NS_UBA;

ButtonWrapper* ButtonWrapper::createByKey(const std::string& key, float size)
{
	auto* obj = new (std::nothrow) ButtonWrapper;
	if (obj && obj->init(key, size))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

bool ButtonWrapper::init(const std::string& key, float size)
{
	if (!Button::init())
		return false;

	loadTextures("textures/button.png", "", "", cocos2d::ui::Widget::TextureResType::LOCAL);
	
	auto label = LabelWrapper::createByKey(key, size);
	if (label)
	{
		label->setPosition(getContentSize() / 2);
		addChild(label);
	}


	return true;
}
