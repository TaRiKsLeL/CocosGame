#include "GameScene.h"


USING_NS_CC;


Scene* GameScene::createScene() {
	return GameScene::create();
}

/*
=====================================================================================================
Init
=====================================================================================================
*/

bool GameScene::init() {

	if (!Scene::init())
	{
		return false;
	}

	Scene::initWithPhysics();


	//this->getPhysicsWorld()->setDebugDrawMask(0xffff);

	
	Enviroment::getInstance()->setScene(this);


	SlaveTraider::getInstance();
	EnemyController::getInstance();

	initContactListeners();
	
	this->scheduleUpdate();

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

void GameScene::removeKeyEventListener(EventListenerKeyboard* listener) {
	this->_eventDispatcher->removeEventListener(listener);
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

