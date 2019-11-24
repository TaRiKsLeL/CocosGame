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
	SlaveTraider::getInstance();


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

	Player* player = nullptr;
	SlaveTraider* slaveTraider = nullptr;
	Citizen* citizen = nullptr;

	if (nodeA && nodeB)
	{

		if (nodeA->getTag() == SprTag::PLAYER || nodeB->getTag() == SprTag::PLAYER)
			player = Player::getInstance();

		if (nodeA->getTag() == SprTag::SLAVE_TRAIDER || nodeB->getTag() == SprTag::SLAVE_TRAIDER)
			slaveTraider = SlaveTraider::getInstance();


		if (nodeA->getTag() == SprTag::CITIZEN)
		{
			citizen = CitizenController::getInstance()->findByPosition(nodeA->getPosition());
		}
		else if(nodeB->getTag() == SprTag::CITIZEN)
			citizen = CitizenController::getInstance()->findByPosition(nodeB->getPosition());


		if(player != nullptr)
		if (player && slaveTraider) {
			log("%d", player->getMoney());

			log("slave pay");
			player->setPayable(slaveTraider);
		}
		else if (player && citizen) {
			log("%d", player->getMoney());

			log("citizen pay");
			player->setPayable(citizen);
		}

	}

	return true;
}

/*
=====================================================================================================
onContactSeparate
=====================================================================================================
*/


bool GameScene::onContactSeparate(PhysicsContact& contact)
{

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Player* player = nullptr;
	SlaveTraider* slaveTraider = nullptr;
	Citizen* citizen = nullptr;

	IPayable* payable;


		if (nodeA->getTag() == SprTag::PLAYER || nodeB->getTag() == SprTag::PLAYER)
			player = Player::getInstance();
		
		if (nodeA->getTag() == SprTag::SLAVE_TRAIDER || nodeB->getTag() == SprTag::SLAVE_TRAIDER) {
			slaveTraider = SlaveTraider::getInstance();
			payable = dynamic_cast<IPayable*>(slaveTraider);
		}
		
		//переробити {

		if (nodeA->getTag() == SprTag::CITIZEN) {
			citizen = CitizenController::getInstance()->findByPosition(nodeA->getPosition());
			payable = dynamic_cast<IPayable*>(citizen);
		}
		else if (nodeB->getTag() == SprTag::CITIZEN) {
			citizen = CitizenController::getInstance()->findByPosition(nodeB->getPosition());
			payable = dynamic_cast<IPayable*>(citizen);
		}

		//}

		if (player != nullptr && player->focused() ) {
			if(player->checkFocusedObj(payable))
				player->removeFocusActListener();
		}
	

	return true;
}

