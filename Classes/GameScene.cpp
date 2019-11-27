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


	this->getPhysicsWorld()->setDebugDrawMask(0xffff);

	
	
	Enviroment::getInstance()->setScene(this);
	
	int sum = PLAYER_START_MONEY;
	BuildingController::getInstance()->walls.at(0)->pay(sum);
	BuildingController::getInstance()->walls.at(1)->pay(sum);
	Enviroment::getInstance()->setBorders(BuildingController::getInstance()->getKingdomBorders());
	



	SlaveTraider::getInstance();






	EventListenerPhysicsContact* playerContactListener = EventListenerPhysicsContact::create();
	playerContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onPlayerContactBegin, this);
	playerContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onPlayerContactSeparate, this);
	
	
	
	
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(playerContactListener, this);

	
	
	
	
	log("post Init");
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
	log("i removed)))");
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

