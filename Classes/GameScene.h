#pragma once

#include "MainMenu.h"
#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float);
	virtual void setKeyEvent();
	void newMenuCallback(cocos2d::Ref* pSender);


};


#pragma once
