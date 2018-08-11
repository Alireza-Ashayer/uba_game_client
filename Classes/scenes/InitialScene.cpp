#include "InitialScene.h"
#include "ui_wrappers/LabelWrapper.h"
#include "LoginScene.h"
#include "RegisterScene.h"
#include "GameScene.h"
#include "singletons/StringCache.h"
#include "singletons/User.h"

USING_NS_CC;
USING_NS_CC_UI;
USING_NS_UBA;

Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = InitialScene::create();

    scene->addChild(layer);

    return scene;
}

bool InitialScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    

	if (!createUI())
		return false;
	


    return true;
}

bool InitialScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("textures/background.jpg");
	if (background)
	{
		background->setPosition(visibleSize / 2);
		addChild(background);
	}


	auto welcomeLabel = LabelWrapper::createByKey("WELCOME", 36);
	if (welcomeLabel)
	{
		welcomeLabel->setPosition(visibleSize / 2 + Size(0, 150));
		welcomeLabel->setTextColor(Color4B::BLACK);
		addChild(welcomeLabel);
	}


	_usernameField = TextBoxWrapper::createByKey("Please enter your name", 24);
	if (_usernameField)
	{
		_usernameField->setName("username_textbox");
		_usernameField->setPosition(visibleSize / 2 + Size(0, 50));
		_usernameField->setMaxLength(24);
		_usernameField->setMaxLengthEnabled(true);
		_usernameField->addEventListener(CC_CALLBACK_2(InitialScene::textFieldEvent, this));
		addChild(_usernameField);
	}


	_maleCheckBox = CheckBoxWrapper::createByKey("MALE", false);
	if (_maleCheckBox)
	{
		_maleCheckBox->setName("male_checkbox");
		_maleCheckBox->setPosition(visibleSize / 2 + Size(-100, 0));
		_maleCheckBox->addEventListener(CC_CALLBACK_2(InitialScene::checkBoxEvent, this));
		addChild(_maleCheckBox);
	}

	_femaleCheckBox = CheckBoxWrapper::createByKey("FEMALE", false);
	if (_femaleCheckBox)
	{
		_femaleCheckBox->setName("female_checkbox");
		_femaleCheckBox->setPosition(visibleSize / 2 + Size(50, 0));
		_femaleCheckBox->addEventListener(CC_CALLBACK_2(InitialScene::checkBoxEvent, this));
		addChild(_femaleCheckBox);
	}


	_youngCheckBox = CheckBoxWrapper::createByKey("Age: -40", false);
	if (_youngCheckBox)
	{
		_youngCheckBox->setName("young_checkbox");
		_youngCheckBox->setPosition(visibleSize / 2 + Size(-100, -50));
		_youngCheckBox->addEventListener(CC_CALLBACK_2(InitialScene::checkBoxEvent, this));
		addChild(_youngCheckBox);
	}

	_oldCheckBox = CheckBoxWrapper::createByKey("Age: +40", false);
	if (_oldCheckBox)
	{
		_oldCheckBox->setName("old_checkbox");
		_oldCheckBox->setPosition(visibleSize / 2 + Size(50, -50));
		_oldCheckBox->addEventListener(CC_CALLBACK_2(InitialScene::checkBoxEvent, this));
		addChild(_oldCheckBox);
	}


	if (_maleCheckBox && _femaleCheckBox)
	{
		_maleCheckBox->setUserData(_femaleCheckBox);
		_femaleCheckBox->setUserData(_maleCheckBox);
	}

	if (_youngCheckBox && _oldCheckBox)
	{
		_youngCheckBox->setUserData(_oldCheckBox);
		_oldCheckBox->setUserData(_youngCheckBox);
	}

	

	//play button
	_playButton = ButtonWrapper::createByKey("PLAY", 24);
	if (_playButton)
	{
		_playButton->setName("play_button");
		_playButton->addTouchEventListener(CC_CALLBACK_2(InitialScene::buttonCallback, this));
		_playButton->setPosition(visibleSize / 2 + Size(0, -150));
		_playButton->setBright(false);
		addChild(_playButton);
	}

	return true;
}


void uba::InitialScene::buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type)
{
	if (type == ui::Button::TouchEventType::ENDED)
	{
		auto button = static_cast<ButtonWrapper*>(pSender);
		auto name = button->getName();

		if (name == "login_button")
		{
			auto scene = LoginScene::createScene();
			if (scene)
			{
				Director::getInstance()->pushScene(scene);
			}
		}
		else if (name == "register_button")
		{
			auto scene = RegisterScene::createScene();
			if (scene)
			{
				Director::getInstance()->pushScene(scene);
			}
		}
		else if (name == "play_button")
		{
			if (_usernameField->getString().size() < 1)
			{
				_usernameField->setPlaceHolder(StringCache::getInstance().getStringByKey("USER_NAME_ERROR"));
				_usernameField->setPlaceHolderColor(Color4B::RED);
			}
			else
			{
				auto username = _usernameField->getString();

				std::string sex;
				std::string ageGroup;

				if (_maleCheckBox->isSelected())
					sex = "male";
				else if (_femaleCheckBox->isSelected())
					sex = "female";
				else
					sex = "";

				if (_oldCheckBox->isSelected())
					ageGroup = "+40";
				else if (_youngCheckBox->isSelected())
					ageGroup = "-40";
				else
					ageGroup = "";



				User::getInstance().init(username, sex, ageGroup);

				auto scene = GameScene::createScene();
				if (scene)
				{
					Director::getInstance()->pushScene(scene);
				}
			}

		}
	}
	
}


void uba::InitialScene::textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type)
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

	auto textField = static_cast<TextBoxWrapper*>(pSender);
	if (textField->getString().size() > 1)
	{
		_playButton->setBright(true);
	}
	else
	{
		_playButton->setBright(false);
	}

}

void uba::InitialScene::checkBoxEvent(Ref* pSender, CheckBox::EventType type)
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
			//otherCheckbox->setSelected(true);
		}
	}
	break;

	default:
		break;
	}

}