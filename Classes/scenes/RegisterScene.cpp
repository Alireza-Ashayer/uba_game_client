#include "RegisterScene.h"
#include "ui_wrappers/LabelWrapper.h"

USING_NS_CC;
USING_NS_CC_UI;
USING_NS_UBA;

Scene* RegisterScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = RegisterScene::create();

    scene->addChild(layer);

    return scene;
}

bool RegisterScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    

	if (!createUI())
		return false;
	


    return true;
}

bool RegisterScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("textures/background.jpg");
	if (background)
	{
		background->setPosition(visibleSize / 2);
		addChild(background);
	}


	auto signupLabel = LabelWrapper::createByKey("SIGN_UP", 36);
	if (signupLabel)
	{
		signupLabel->setPosition(visibleSize / 2 + Size(0, 250));
		signupLabel->setTextColor(Color4B::BLACK);
		addChild(signupLabel);
	}


	//create text boxes
	for (unsigned int i = 0; i < 5; ++i)
	{
		std::string placeHolderKey;

		switch (i)
		{
		case 0:
			placeHolderKey = "FIRST_NAME";
			break;
		case 1:
			placeHolderKey = "LAST_NAME";
			break;
		case 2:
			placeHolderKey = "YOUR_EMAIL";
			break;
		case 3:
			placeHolderKey = "RE_ENTER_EMAIL";
			break;
		case 4:
			placeHolderKey = "NEW_PASSWORD";
			break;
		}


		int offsetY = (-(int)i) * 60;

		auto textbox = TextBoxWrapper::createByKey(placeHolderKey, 24);
		if (textbox)
		{
			textbox->setName(placeHolderKey);
			textbox->setPosition(visibleSize / 2 + Size(0, 150 + offsetY));
			textbox->setMaxLength(24);
			textbox->setMaxLengthEnabled(true);
			textbox->addEventListener(CC_CALLBACK_2(RegisterScene::textFieldEvent, this));
			addChild(textbox);


			if (i == 4)
			{
				textbox->setPasswordEnabled(true);
			}
		}
	}


	//create gender option
	auto maleCheckBox = CheckBoxWrapper::createByKey("MALE", true);
	if (maleCheckBox)
	{
		maleCheckBox->setName("male_checkbox");
		maleCheckBox->setPosition(visibleSize / 2 + Size(-100, -160));
		maleCheckBox->addEventListener(CC_CALLBACK_2(RegisterScene::checkBoxEvent, this));
		addChild(maleCheckBox);
	}

	auto femaleCheckBox = CheckBoxWrapper::createByKey("FEMALE", false);
	if (femaleCheckBox)
	{
		maleCheckBox->setName("female_checkbox");
		femaleCheckBox->setPosition(visibleSize / 2 + Size(50, -160));
		femaleCheckBox->addEventListener(CC_CALLBACK_2(RegisterScene::checkBoxEvent, this));
		addChild(femaleCheckBox);
	}
	
	if (maleCheckBox && femaleCheckBox)
	{
		maleCheckBox->setUserData(femaleCheckBox);
		femaleCheckBox->setUserData(maleCheckBox);
	}

	
	//register button
	auto registerButton = ButtonWrapper::createByKey("REGISTER", 24);
	if (registerButton)
	{
		registerButton->setName("register_button");
		registerButton->addTouchEventListener(CC_CALLBACK_2(RegisterScene::buttonCallback, this));
		registerButton->setPosition(visibleSize / 2 + Size(100, -250));
		addChild(registerButton);
	}

	//cancel button
	auto cancelButton = ButtonWrapper::createByKey("CANCEL", 24);
	if (cancelButton)
	{
		cancelButton->setName("cancel_button");
		cancelButton->addTouchEventListener(CC_CALLBACK_2(RegisterScene::buttonCallback, this));
		cancelButton->setPosition(visibleSize / 2 + Size(-100, -250));
		addChild(cancelButton);
	}


	return true;
}

void uba::RegisterScene::textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type)
{
	//this callback will be used for analytics
	auto node = static_cast<cocos2d::Node*>(pSender);
	auto name = node->getName();

	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		node->setColor(Color3B::RED);
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		node->setColor(Color3B::WHITE);
		break;
	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
		break;
	default:
		break;
	}

}


void uba::RegisterScene::checkBoxEvent(Ref* pSender, CheckBox::EventType type)
{
	auto senderCheckbox = static_cast<CheckBoxWrapper*>(pSender);

	CheckBoxWrapper* otherCheckbox = nullptr;
	if (senderCheckbox->getUserData() != nullptr)
	{
		otherCheckbox = static_cast<CheckBoxWrapper*>(senderCheckbox->getUserData());
	}

	switch (type)
	{
	case CheckBox::EventType::SELECTED:
	{
		if (otherCheckbox)
		{
			otherCheckbox->setSelected(false);
		}
	}
		break;

	case CheckBox::EventType::UNSELECTED:
	{
		if (otherCheckbox)
		{
			otherCheckbox->setSelected(true);
		}
	}
		break;

	default:
		break;
	}

}

void uba::RegisterScene::buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type)
{
	if (type == Button::TouchEventType::ENDED)
	{
		auto button = static_cast<ButtonWrapper*>(pSender);
		auto name = button->getName();

		if (name == "register_button")
		{
			//TODO
		}
		else if (name == "cancel_button")
		{
			Director::getInstance()->popScene();
		}
	}
}
