#pragma once

#include "MainMenu.h"
#include "cocos2d.h"
#include "GameTime.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float);
	virtual void setKeyEvent();
	//virtual void newMenuCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GameScene);
};
