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
		"exitBtn.png",
		"exitBtn.png"
	);
	btnImages->push_back(bufferBtmImage);

	
	bufferBtmImage = MenuItemImage::create(
		"continueBtn.png",
		"continueBtn.png"
	);
	btnImages->push_back(bufferBtmImage);


	bufferBtmImage = MenuItemImage::create(
		"newGameBtn.png",
		"newGameBtn.png"
	);
	btnImages->push_back(bufferBtmImage);


	bufferBtmImage = MenuItemImage::create(
		"settingsBtn.png",
		"settingsBtn.png"
	);
	btnImages->push_back(bufferBtmImage);

	
	btnCallbacks->push_back(&MainMenu::mainMenuCallback);
	btnCallbacks->push_back(&MainMenu::settingsCallback);
	btnCallbacks->push_back(&MainMenu::menuCloseCallback);
	btnCallbacks->push_back(&MainMenu::menuCloseCallback);

	menu = Menu::create();

	for (int i = 0; i < btnCallbacks->size(); i++)
	{
		bufferBtmImage = btnImages->at(i);

		scenesCallMap.insert(pair< int, BtmCallBack >(bufferBtmImage->_ID, btnCallbacks->at(i)));

		bufferBtmImage->setCallback([&](Ref* sender) {
			void (MainMenu:: * tmpFunc)(Ref*) = scenesCallMap.at(sender->_ID);
			(this->*tmpFunc)(sender);
			});

		bufferBtmImage->setPosition(Vec2(
			(origin.x + visibleSize.width) / 2,
			(origin.y + visibleSize.height)/ btnCallbacks->size()  + (200 * i)));

		menu->addChild(bufferBtmImage);

	}

	menu->setPosition(Vec2::ZERO);


	Label* label = Label::createWithTTF("Kalush", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));


	Sprite* background = Sprite::create("background.png");

	background->setAnchorPoint(cocos2d::Vec2(0, 0));

	this->addChild(background, 0);
	this->addChild(label, 1);
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
