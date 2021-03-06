#ifndef GameScene_h__
#define GameScene_h__

#include "cocos2d.h"

#include "macros/AppMacros.h"
#include "ui_wrappers/ButtonWrapper.h"
#include "entities/Entity.h"

NS_UBA_BEGIN


class PlayerEntity;
class LabelWrapper;

enum class GameState
{
	RUNNING,
	LOST
};

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

private:
	CREATE_FUNC(GameScene);

	GameScene();

    bool init() override;
	void update(float dt) override;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
	bool createBackground();
	bool createGameLayer();
	void addHazard();
	void addEndingPopup();

	void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Button::TouchEventType type);
	void addSwipeAnalytics(bool isUp);
	void touchEndCallback(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void accEventCallback(cocos2d::Acceleration *accData, cocos2d::Event *unused_event);


	int64_t _swipeStartTime;

	cocos2d::Layer* _gameLayer;
	cocos2d::Vec2 _touchStartPosition;
	cocos2d::Vector<Entity*> _entites;
	PlayerEntity* _playerEntity;
	LabelWrapper* _scoreLabel;

	GameState _gameState;

	double _gameSpeed;
	double _score;
	int _scoreInt;
	int _lastAddPosition;
	int _screenBlockCountHorizontal;

	std::vector<std::pair<int64_t, cocos2d::Vec2>> _currentSwipeData;

	cocos2d::Vec3 _currentAcc;
	std::vector<cocos2d::Vec3> _accs;
};

NS_UBA_END

#endif // GameScene_h__

