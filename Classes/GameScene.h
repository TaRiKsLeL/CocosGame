#pragma once

#include "MainMenu.h"
#include "Enviroment.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float);
	virtual void setKeyEventListener(EventListenerKeyboard* listener, Sprite* sprite);
	//virtual void newMenuCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GameScene);
};
