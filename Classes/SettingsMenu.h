#pragma once

#include "MainMenu.h"
#include "cocos2d.h"

class SettingsMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void newMenuCallback(cocos2d::Ref* pSender);


	//	CREATE_FUNC(SecondScene);

};


#pragma once
