#ifndef TextBoxWrapper_h__
#define TextBoxWrapper_h__


#include "ui/UITextField.h"
#include "macros/AppMacros.h"

#include <string>

NS_UBA_BEGIN

class TextBoxWrapper : public cocos2d::ui::TextField
{
public:
	static TextBoxWrapper* createByKey(const std::string& placeholderKey, float size);

private:

	bool init(const std::string& placeholderKey, float size);


};

NS_UBA_END

#endif // TextBoxWrapper_h__
