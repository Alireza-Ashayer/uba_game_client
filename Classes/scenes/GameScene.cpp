#include "GameScene.h"
#include "ui_wrappers/LabelWrapper.h"
#include "LoginScene.h"
#include "RegisterScene.h"
#include "entities/GroundEntity.h"
#include "entities/PlayerEntity.h"
#include "entities/HazardEntity.h"
#include "singletons/Analytics.h"

USING_NS_CC;
USING_NS_CC_UI;
USING_NS_UBA;

const int JUMP_SWIPE_TELORANCE = 5;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}


uba::GameScene::GameScene()
	: _gameSpeed(3.5f)
	, _lastAddPosition(0)
	, _screenBlockCountHorizontal(0)
	, _playerEntity(nullptr)
	, _touchStartPosition(Vec2::ZERO)
	, _gameState(GameState::RUNNING)
	, _scoreLabel(nullptr)
	, _score(0)
	, _scoreInt(0)
{

}


bool GameScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
        return false;
    

	_entites = cocos2d::Vector<Entity*>();

	if (!createBackground())
		return false;
	
	if (!createGameLayer())
		return false;


	scheduleUpdate();

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	eventListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    return true;
}



bool uba::GameScene::createBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	Texture2D::TexParams texParams;
	texParams.magFilter = GL_LINEAR;
	texParams.minFilter = GL_LINEAR;
	texParams.wrapS = GL_REPEAT;
	texParams.wrapT = GL_REPEAT;

	auto bgTile = Sprite::create("textures/level_bgtile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	if (bgTile)
	{
		bgTile->getTexture()->setTexParameters(texParams);
		bgTile->setPosition(origin + visibleSize / 2);
		addChild(bgTile);

		return true;
	}
	

	return false;
}



bool uba::GameScene::createGameLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	_gameLayer = Layer::create();
	if (_gameLayer)
	{
		_gameLayer->setPosition(origin + Vec2(0, visibleSize.height / 2 - 50));
		addChild(_gameLayer);

		_screenBlockCountHorizontal = 1 + visibleSize.width / Entity::BLOCK_SIZE;
		
		for (int i = 0; i < _screenBlockCountHorizontal; i++)
		{
			auto groundEntity = GroundEntity::create(i);
			if (groundEntity)
			{
				_gameLayer->addChild(groundEntity);
				_entites.pushBack(groundEntity);
			}
		}

		_playerEntity = PlayerEntity::create(_screenBlockCountHorizontal / 2);
		if (_playerEntity)
		{
			_gameLayer->addChild(_playerEntity);
			_entites.pushBack(_playerEntity);
		}


		_scoreLabel = LabelWrapper::createByKey("", 24);
		if (_scoreLabel)
		{
			_scoreLabel->setPosition(visibleSize + Size(-100, -50));
			addChild(_scoreLabel);
		}
		

		return true;
	}

	
	return false;
}



void uba::GameScene::buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type)
{
	if (type == ui::Button::TouchEventType::ENDED)
	{
		auto button = static_cast<ButtonWrapper*>(pSender);
		auto name = button->getName();

		if (name == "restart_button")
		{
			auto gameScene = GameScene::createScene();
			if (gameScene)
			{
				Director::getInstance()->replaceScene(gameScene);
			}
		}
		else if (name == "exit_button")
		{
			Director::getInstance()->popScene();
		}
	}
}

void uba::GameScene::update(float dt)
{
	LayerColor::update(dt);

	if (_gameState == GameState::LOST)
	{
		return;
	}

	_score += dt;

	auto newScoreInt = (int)_score;
	if (newScoreInt != _scoreInt)
	{
		_scoreLabel->setString(StringUtils::toString(newScoreInt));
		_scoreInt = newScoreInt;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();


	bool putHazard = false;

	auto it = _entites.begin();

	while (it != std::end(_entites)) {
		
		auto entity = *it;

		if (!entity->isStatic())
		{
			entity->setPositionX(entity->getPositionX() - _gameSpeed);

			if (entity->getPositionX() + Entity::BLOCK_SIZE < 0)
			{
				if (entity->removeOnExit())
				{
					entity->removeFromParent();
					it = _entites.erase(it);
					continue;
				}
				else
				{
					entity->moveToFront(_screenBlockCountHorizontal);
					if (entity->getIndex() % 4 == 0)
					{
						putHazard = true;
					}
				}
			}

			if (entity->isHazard())
			{
				if (_playerEntity->collidesWith(entity))
				{
					_gameSpeed = 0;
					addEndingPopup();
				}
			}
		}

		++it;
	}

	if (putHazard)
	{
		addHazard();
	}
}

bool uba::GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (_gameState == GameState::LOST)
	{
		return false;
	}

	if (_touchStartPosition.length() == 0)
	{
		_touchStartPosition = touch->getLocationInView();
		_swipeStartTime = utils::getTimeInMilliseconds();
		return true;
	}

	return false;
}

void uba::GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void uba::GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (_touchStartPosition.length() != 0)
	{
        auto distance = _touchStartPosition.y - touch->getLocationInView().y;
		if (distance > JUMP_SWIPE_TELORANCE)
		{
			_playerEntity->switchPlayerState(PlayerState::JUMP);
		}
		else if (distance < JUMP_SWIPE_TELORANCE)
		{
			_playerEntity->switchPlayerState(PlayerState::SLIDE);
		}

        
        if (std::abs(distance) > 5) {
            auto swipeTimeDelta = utils::getTimeInMilliseconds() - _swipeStartTime;
            addSwipeAnalytics(_touchStartPosition, touch->getLocationInView(), swipeTimeDelta);
        }
		

		_touchStartPosition = Vec2::ZERO;
	}
}

void uba::GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (_touchStartPosition.length() != 0)
	{
		auto distance = _touchStartPosition.y - touch->getLocationInView().y;
		if (distance > JUMP_SWIPE_TELORANCE)
		{
			_playerEntity->switchPlayerState(PlayerState::JUMP);
		}
		else if (distance < JUMP_SWIPE_TELORANCE)
		{
			_playerEntity->switchPlayerState(PlayerState::SLIDE);
		}


		if (std::abs(distance) > 5) {
			auto swipeTimeDelta = utils::getTimeInMilliseconds() - _swipeStartTime;
			addSwipeAnalytics(_touchStartPosition, touch->getLocationInView(), swipeTimeDelta);
		}


		_touchStartPosition = Vec2::ZERO;
	}

}

void uba::GameScene::addHazard()
{
	auto hazard = HazardEntity::create(_screenBlockCountHorizontal);
	if (hazard)
	{
		_gameLayer->addChild(hazard);
		_entites.pushBack(hazard);
	}
}

void uba::GameScene::addEndingPopup()
{
	_gameState = GameState::LOST;

	auto layer = LayerColor::create(cocos2d::Color4B(Color3B::BLACK, 150));
	if (layer)
	{
		layer->setContentSize(Director::getInstance()->getVisibleSize());
		addChild(layer, 100);

		auto restartButton = ButtonWrapper::createByKey("RESTART", 24);
		if (restartButton)
		{
			restartButton->setName("restart_button");
			restartButton->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonCallback, this));
			restartButton->setPosition(layer->getContentSize() / 2 + Size(100, 0));
			layer->addChild(restartButton);
		}

		auto exitButton = ButtonWrapper::createByKey("EXIT", 24);
		if (exitButton)
		{
			exitButton->setName("exit_button");
			exitButton->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonCallback, this));
			exitButton->setPosition(layer->getContentSize() / 2 + Size(-100, 0));
			layer->addChild(exitButton);
		}
	}
}

void uba::GameScene::addSwipeAnalytics(cocos2d::Vec2 startPos, cocos2d::Vec2 endPos, int parameter)
{
	std::string direction = "up";


	AnalyticsData aData;
	aData.category = "swipe";
	aData.direction = "up";
	aData.parameter = parameter;

	Analytics::getInstance().addAnalyticsData(aData, true);
}
