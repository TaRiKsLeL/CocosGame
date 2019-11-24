#include "MainMenu.h"
#include "SettingsMenu.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include <map> 

using namespace std;
USING_NS_CC;

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}


typedef void (MainMenu::* BtmCallBack)(Ref*);

MenuItemImage* bufferBtmImage;
Menu* menu;

map <int, BtmCallBack> scenesCallMap;
vector < BtmCallBack>* btnCallbacks;
vector < MenuItemImage*>* btnImages;


bool MainMenu::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	void (MainMenu:: * pointer)(Ref*);

	btnCallbacks = new vector < BtmCallBack>();
	btnImages = new vector < MenuItemImage*>();


	bufferBtmImage = MenuItemImage::create(
		EXIT_BTN,
		EXIT_BTN
	);
	bufferBtmImage->setScale(SCALE_FACTOR);
	btnImages->push_back(bufferBtmImage);


	bufferBtmImage = MenuItemImage::create(
		SETTINGS_BTN,
		SETTINGS_BTN
	);
	bufferBtmImage->setScale(SCALE_FACTOR);
	btnImages->push_back(bufferBtmImage);
	
	bufferBtmImage = MenuItemImage::create(
		CONTINUE_BTN,
		CONTINUE_BTN
	);
	bufferBtmImage->setScale(SCALE_FACTOR);
	btnImages->push_back(bufferBtmImage);


	bufferBtmImage = MenuItemImage::create(
		NEW_GAME_BTN,
		NEW_GAME_BTN
	);
	bufferBtmImage->setScale(SCALE_FACTOR);
	btnImages->push_back(bufferBtmImage);
	
	btnCallbacks->push_back(&MainMenu::menuCloseCallback);
	btnCallbacks->push_back(&MainMenu::settingsCallback);
	btnCallbacks->push_back(&MainMenu::newGameCallback);
	btnCallbacks->push_back(&MainMenu::newGameCallback);

	menu = Menu::create();

	for (int i = 0; i < btnCallbacks->size(); i++)
	{
		bufferBtmImage = btnImages->at(i);
		bufferBtmImage->setAnchorPoint(Vec2(0.5, 1));
		scenesCallMap.insert(pair< int, BtmCallBack >(bufferBtmImage->_ID, btnCallbacks->at(i)));

		bufferBtmImage->setCallback([&](Ref* sender) {
			void (MainMenu:: * tmpFunc)(Ref*) = scenesCallMap.at(sender->_ID);
			(this->*tmpFunc)(sender);
			});

		bufferBtmImage->setPosition(Vec2(
			(origin.x + visibleSize.width) / 2,
			(origin.y + visibleSize.height)/ btnCallbacks->size()  + (visibleSize.height / btnCallbacks->size() * i)));

		menu->addChild(bufferBtmImage);

	}

	menu->setPosition(Vec2::ZERO);



	Sprite* background = Sprite::create("background.png");

	background->setAnchorPoint(cocos2d::Vec2(0, 0));

	this->addChild(background, 0);
	this->addChild(menu, 1);

	return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void MainMenu::newGameCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void MainMenu::settingsCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(SettingsMenu::createScene());
}
void MainMenu::mainMenuCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(this->createScene());
}
