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
	
	int sum = PLAYER_START_MONEY;
	
	UI::getInstance()->createCoinsLabel(to_string(sum), COINS_AMOUNT_FONT, COINS_LABEL_SIZE);
	UI::getInstance()->createCoin(COIN_FRAMES, COIN_IMAGES_AMOUNT, COIN_IMAGE_SIZE, COIN_TIME_PER_FRAME);
	UI::getInstance()->createHeart(FULL_HEART_FRAMES, EMPTY_HEART_FRAMES, HEART_IMAGES_AMOUNT, HEART_IMAGE_SIZE, HEART_TIME_PER_FRAME);

	SlaveTraider::getInstance();
	EnemyController::getInstance();





	EventListenerPhysicsContact* playerContactListener = EventListenerPhysicsContact::create();
	playerContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onPlayerContactBegin, this);
	playerContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onPlayerContactSeparate, this);
	
	EventListenerPhysicsContact* builderContactListener = EventListenerPhysicsContact::create();
	builderContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onBuilderContactBegin, this);
	builderContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onBuilderContactSeparate, this);

	
	
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(playerContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(builderContactListener, this);

	
	
	
	
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

