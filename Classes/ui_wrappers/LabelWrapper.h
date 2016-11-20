#ifndef LabelWrapper_h__
#define LabelWrapper_h__

#include "ui/UIText.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class LabelWrapper : public cocos2d::ui::Text
{
public:
	static LabelWrapper* createByKey(const std::string& key, float size);

private:

	bool init(const std::string& key, float size);


};

NS_UBA_END

#endif // LabelWrapper_h__
