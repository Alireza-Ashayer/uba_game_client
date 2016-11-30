#ifndef CheckBoxWrapper_h__
#define CheckBoxWrapper_h__


#include "ui/UICheckBox.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class CheckBoxWrapper : public cocos2d::ui::CheckBox
{
public:
	static CheckBoxWrapper* createByKey(const std::string& key, bool isChecked);

private:

	bool init(const std::string& key, bool isChecked);


};

NS_UBA_END

#endif // CheckBoxWrapper_h__
