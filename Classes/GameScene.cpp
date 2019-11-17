#include "GameScene.h"


using namespace cocos2d;

USING_NS_CC;

EventListenerKeyboard* listener;

Scene* GameScene::createScene() {
	return GameScene::create();
}


bool GameScene::init() {
	cocos2d::log("some word");

	if (!Scene::init())
	{
		return false;
	}

	//Scene::initWithPhysics();

	//GameScene::getPhysicsWorld()->setGravity(Vec2(0, -98 * 8));
	//this->getPhysicsWorld()->setDebugDrawMask(0xffff);


	listener = EventListenerKeyboard::create();
	GameScene::setKeyEvent();
//	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);
	this->scheduleUpdate();


	//EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(Platform::onContactBegin, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	return true;
}

/*
=====================================================================================================
KeyHandler
=====================================================================================================
*/

void GameScene::setKeyEvent() {
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {



	};
}

/*
=====================================================================================================
Update
=====================================================================================================
*/

void GameScene::update(float time)
{
	GameTime::updateFrame();
}


