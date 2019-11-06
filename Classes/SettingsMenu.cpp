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

	return true;
}
