#include "LabelWrapper.h"

#include "singletons/StringCache.h"

USING_NS_UBA;

LabelWrapper* LabelWrapper::createByKey(const std::string& key, float size)
{
	auto* obj = new (std::nothrow) LabelWrapper;
	if (obj && obj->init(key, size))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

bool LabelWrapper::init(const std::string& key, float size)
{
	if (!Text::init())
		return false;

	setFontName("fonts/arial.ttf");
	setFontSize(size);
	setString(StringCache::getInstance().getStringByKey(key));

	return true;
}
