#include "CheckBoxWrapper.h"

#include "singletons/StringCache.h"
#include "ui_wrappers/LabelWrapper.h"

USING_NS_UBA;

CheckBoxWrapper* CheckBoxWrapper::createByKey(const std::string& key, bool isChecked)
{
	auto* obj = new (std::nothrow) CheckBoxWrapper;
	if (obj && obj->init(key, isChecked))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

bool CheckBoxWrapper::init(const std::string& key, bool isChecked)
{
	if (!CheckBox::init())
		return false;

	setSelected(isChecked);
	loadTextures("textures/check_box_field.png", "", "textures/check_box_mark.png", "", "", cocos2d::ui::Widget::TextureResType::LOCAL);

	auto label = LabelWrapper::createByKey(key, 22);
	if (label)
	{
		label->setPosition(getContentSize() / 2 + cocos2d::Size(25, 0));
		label->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
		label->setColor(cocos2d::Color3B::BLACK);
		addChild(label);
	}


	return true;
}
