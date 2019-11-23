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


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

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

/*
=====================================================================================================
onContact
=====================================================================================================
*/

bool GameScene::onContactBegin(PhysicsContact& contact)
{

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Player* player;
	SlaveTraider* slaveTraider;
	Building* building;

	if (nodeA && nodeB)
	{

		if (nodeA->getTag() == SprTag::PLAYER || nodeB->getTag() == SprTag::PLAYER)
			player = Player::getInstance();

		if (nodeA->getTag() == SprTag::SLAVE_TRAIDER || nodeB->getTag() == SprTag::SLAVE_TRAIDER)
			slaveTraider = SlaveTraider::getInstance();

		if (player && slaveTraider) {
			player->setPayable(slaveTraider);
		}

		//if(nodeA->getTag()==SprTag::BUILDING || nodeB->getTag()==SprTag::BUILDING)
			//building
	}

	return true;
}

bool GameScene::onContactSeparate(PhysicsContact& contact)
{

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Player* player;
	SlaveTraider* slaveTraider;

	if (nodeA && nodeB)
	{

		if (nodeA->getTag() == SprTag::PLAYER || nodeB->getTag() == SprTag::PLAYER)
			player = Player::getInstance();

		if (nodeA->getTag() == SprTag::SLAVE_TRAIDER || nodeB->getTag() == SprTag::SLAVE_TRAIDER)
			slaveTraider = SlaveTraider::getInstance();

		if (player && slaveTraider) {
			player->removeActListener();
		}
	}

	return true;
}

