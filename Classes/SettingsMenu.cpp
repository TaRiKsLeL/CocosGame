#include "SettingsMenu.h"
#include "MainMenu.h"
#include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;



Scene* SettingsMenu::createScene() {
	return SettingsMenu::create();
}


bool SettingsMenu::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto menu = Menu::create();

	this->addChild(menu);

	Sprite* background = Sprite::create(BACKGROUND_SPR);

	background->setAnchorPoint(cocos2d::Vec2(0, 0));

	this->addChild(background, 0);

	return true;
}
