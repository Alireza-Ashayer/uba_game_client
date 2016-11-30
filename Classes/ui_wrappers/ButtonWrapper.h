#ifndef ButtonWrapper_h__
#define ButtonWrapper_h__


#include "ui/UIButton.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class ButtonWrapper : public cocos2d::ui::Button
{
public:
	static ButtonWrapper* createByKey(const std::string& key, float size);

private:

	bool init(const std::string& key, float size);


};

NS_UBA_END

#endif // ButtonWrapper_h__
