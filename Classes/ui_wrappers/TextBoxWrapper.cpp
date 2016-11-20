#include "TextBoxWrapper.h"

#include "singletons/StringCache.h"

USING_NS_UBA;

TextBoxWrapper* TextBoxWrapper::createByKey(const std::string& placeholderKey, float size)
{
	auto* obj = new (std::nothrow) TextBoxWrapper;
	if (obj && obj->init(placeholderKey, size))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

bool TextBoxWrapper::init(const std::string& placeholderKey, float size)
{
	if (!TextField::init())
		return false;

	setFontName("fonts/arial.ttf");
	setFontSize(size);
	setPlaceHolder(StringCache::getInstance().getStringByKey(placeholderKey));

	return true;
}
