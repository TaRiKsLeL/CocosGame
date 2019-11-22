#include "GameScene.h"


USING_NS_CC;

Scene* GameScene::createScene() {
	return GameScene::create();
}


bool GameScene::init() {

	if (!Scene::init())
	{
		return false;
	}

	//Scene::initWithPhysics();

	//GameScene::getPhysicsWorld()->setGravity(Vec2(0, -98 * 8));
	//this->getPhysicsWorld()->setDebugDrawMask(0xffff);

	Enviroment::getInstance()->setScene(this);
	int sum = 300;
	
	BuildingController::getInstance()->walls.at(0)->pay(sum);
	BuildingController::getInstance()->walls.at(1)->pay(sum);

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

void GameScene::setKeyEventListener(EventListenerKeyboard* listener, Sprite* sprite) {
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
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


