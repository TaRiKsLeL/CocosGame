#pragma once

#include "MainMenu.h"
#include "Data.h"
#include "cocos2d.h"

class SettingsMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void newMenuCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(SettingsMenu);

};

