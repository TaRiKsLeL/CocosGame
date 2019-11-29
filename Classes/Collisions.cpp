#include "GameScene.h"

/*
=====================================================================================================
init ContactListeners
=====================================================================================================
*/

void GameScene::initContactListeners() {
	EventListenerPhysicsContact* playerContactListener = EventListenerPhysicsContact::create();
	playerContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onPlayerContactBegin, this);
	playerContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onPlayerContactSeparate, this);

	EventListenerPhysicsContact* builderContactListener = EventListenerPhysicsContact::create();
	builderContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onBuilderContactBegin, this);
	builderContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onBuilderContactSeparate, this);

	EventListenerPhysicsContact* enemyContactListener = EventListenerPhysicsContact::create();
	enemyContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onEnemyContactBegin, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(playerContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(builderContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(enemyContactListener, this);

}


/*
=====================================================================================================
onContact Player
=====================================================================================================
*/

bool GameScene::onPlayerContactBegin(PhysicsContact& contact)
{
	Player* player = nullptr;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Node* nonPlayerNode = nullptr;

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ PLAYER_CATEGORY_BM) == 0) {
		player = Player::getInstance();
		nonPlayerNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ PLAYER_CATEGORY_BM) == 0) {
		player = Player::getInstance();
		nonPlayerNode = nodeA;
	}
	else
		return false;

	if ((nonPlayerNode->getPhysicsBody()->getCollisionBitmask() & PLAYER_CATEGORY_BM) == 0)
		return false;



	IPayable* payable = getPayableByNode(nonPlayerNode);
	
	if (payable != nullptr)
		player->setPayable(payable);

	return true;
}



/*
=====================================================================================================
onContactSeparate Player
=====================================================================================================
*/


bool GameScene::onPlayerContactSeparate(PhysicsContact& contact)
{

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Player* player = nullptr;
	SlaveTraider* slaveTraider = nullptr;
	Citizen* citizen = nullptr;

	IPayable* payable = nullptr;


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

	Building* building = BuildingController::getInstance()->findBuildingByTagAndPosition(nodeA->getTag(), nodeA->getPosition());

	if (!building) {
		building = BuildingController::getInstance()->findBuildingByTagAndPosition(nodeB->getTag(), nodeB->getPosition());
	}
	if (building)
		payable = dynamic_cast<IPayable*>(building);

	//}

	if (player != nullptr && player->focused()) {
		if (player->checkFocusedObj(payable))
			player->disableFocusBuyListener();
	}


	return true;
}



IPayable* GameScene::getPayableByNode(Node* nonPlayerNode) {

	Building* building = nullptr;
	SlaveTraider* slaveTraider = nullptr;
	Citizen* citizen = nullptr;
	Builder* builder = nullptr;
	Warrior* warrior = nullptr;
	Worker* worker = nullptr;

	IPayable* objToPay = nullptr;

	switch (nonPlayerNode->getTag()) {

	case SprTag::SLAVE_TRAIDER:
		objToPay = dynamic_cast<IPayable*>(SlaveTraider::getInstance());
		break;
	case SprTag::CITIZEN:
		objToPay = dynamic_cast<IPayable*>(CitizenController::getInstance()->findByPosition(nonPlayerNode->getPosition()));
		break;
	case SprTag::BUILDER:
		objToPay = dynamic_cast<IPayable*>(BuilderController::getInstance()->findByPosition(nonPlayerNode->getPosition()));
		break;
	case SprTag::WARRIOR:
		objToPay = dynamic_cast<IPayable*>(WarriorController::getInstance()->findByPosition(nonPlayerNode->getPosition()));
		break;
	case SprTag::WORKER:
		objToPay = dynamic_cast<IPayable*>(WorkerController::getInstance()->findByPosition(nonPlayerNode->getPosition()));
		break;

	case SprTag::MINE:
	case SprTag::TOWER:
	case SprTag::CASTLE:
	case SprTag::WALL:
		building = BuildingController::getInstance()->findBuildingByTagAndPosition(nonPlayerNode->getTag(), nonPlayerNode->getPosition());
		if (Enviroment::getInstance()->getBorders()->isInKingdom(building->getSprite()->getPositionX())) {
			objToPay = dynamic_cast<IPayable*>(building);
		}
		else if (Wall* wall = dynamic_cast<Wall*>(building)) {
			objToPay = dynamic_cast<IPayable*>(building);
		}
		break;
	}
	return objToPay;
}

/*
=====================================================================================================
onContact Builder
=====================================================================================================
*/

bool GameScene::onBuilderContactBegin(PhysicsContact& contact)
{
	Builder* builder = nullptr;
	Building* building = nullptr;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Node* secondNode = nullptr;

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ BUILDER_CATEGORY_BM) == 0) {
		builder = BuilderController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ BUILDER_CATEGORY_BM) == 0) {
		builder = BuilderController::getInstance()->findByPosition(nodeB->getPosition());
		secondNode = nodeA;
	}
	else
		return false;

	if ((secondNode->getPhysicsBody()->getCollisionBitmask() & BUILDER_COLLIDE_BM) == 0)
		return false;

	switch (secondNode->getTag()) {

	case SprTag::MINE:
	case SprTag::TOWER:
	case SprTag::CASTLE:
	case SprTag::WALL:
		building = BuildingController::getInstance()->findBuildingByTagAndPosition(secondNode->getTag(), secondNode->getPosition());
		if (building == nullptr) return false;
		break;
	default:
		return false;
	}

	if (builder && builder->isBuilding() && builder->getCurrentPointMoveTo() == building->getPosition()) {
		builder->stopMoving();
		building->setBuildingStatus(true);
		return true;
	}

	return false;
}

/*
=====================================================================================================
onContactSeparate Builder
=====================================================================================================
*/


bool GameScene::onBuilderContactSeparate(PhysicsContact& contact)
{
	Builder* builder = nullptr;
	Building* building = nullptr;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Node* secondNode = nullptr;

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ BUILDER_CATEGORY_BM) == 0) {
		builder = BuilderController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ BUILDER_CATEGORY_BM) == 0) {
		builder = BuilderController::getInstance()->findByPosition(nodeB->getPosition());
		secondNode = nodeA;
	}
	else
		return false;

	if ((secondNode->getPhysicsBody()->getCollisionBitmask() & BUILDER_COLLIDE_BM) == 0)
		return false;

	switch (secondNode->getTag()) {

	case SprTag::MINE:
	case SprTag::TOWER:
	case SprTag::CASTLE:
	case SprTag::WALL:
		building = BuildingController::getInstance()->findBuildingByTagAndPosition(secondNode->getTag(), secondNode->getPosition());
		if (building == nullptr) return false;
		break;
	default:
		return false;
	}

	if (builder && builder->getCurrentPointMoveTo() == building->getPosition()) {
		builder->setBuild(false);
		building->setBuildingStatus(false);
		return true;
	}

	return false;
}

/*
=====================================================================================================
onContact Enemy
=====================================================================================================
*/

bool GameScene::onEnemyContactBegin(PhysicsContact& contact)
{
	Enemy* enemy = nullptr;
	Node* secondNode = nullptr;

	IAttackable* objToAtt = nullptr;

	bool isWall = false;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ ENEMY_CATEGORY_BM) == 0) {
		enemy = EnemyController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ ENEMY_CATEGORY_BM) == 0) {
		enemy = EnemyController::getInstance()->findByPosition(nodeB->getPosition());
		secondNode = nodeA;
	}
	else
		return false;

	if ((secondNode->getPhysicsBody()->getCollisionBitmask() & ENEMY_COLLIDE_BM) == 0)
		return false;

	switch (secondNode->getTag()) {
	case SprTag::WALL:
		isWall = true;
		objToAtt = static_cast<IAttackable*>(BuildingController::getInstance()->findWallByPos(secondNode->getPosition()));
		break;
	case SprTag::PLAYER:
		objToAtt = static_cast<IAttackable*>(Player::getInstance());
		break;
	case SprTag::CASTLE:
		objToAtt = static_cast<IAttackable*>(BuildingController::getInstance()->getCastle());
		break;
	case SprTag::CITIZEN:
		objToAtt = static_cast<IAttackable*>(CitizenController::getInstance()->findByPosition(secondNode->getPosition()));
		break;
	case SprTag::WARRIOR:
		objToAtt = static_cast<IAttackable*>(WarriorController::getInstance()->findByPosition(secondNode->getPosition()));
		break;
	case SprTag::WORKER:
		objToAtt = static_cast<IAttackable*>(WorkerController::getInstance()->findByPosition(secondNode->getPosition()));
		break;
	case SprTag::BUILDER:
		objToAtt = static_cast<IAttackable*>(BuilderController::getInstance()->findByPosition(secondNode->getPosition()));
		break;
	default:
		return false;
	}

	if (objToAtt != nullptr && objToAtt->canBeAttacked()) {
		objToAtt->hit(enemy->getAttPower());
		enemy->jmpBack();
	}
	return false;
}

IAttackable* GameScene::getAttackableByNode(Node* node) {

	Building* building = nullptr;
	SlaveTraider* slaveTraider = nullptr;
	Citizen* citizen = nullptr;
	Builder* builder = nullptr;
	Warrior* warrior = nullptr;

	IAttackable* objToAttack = nullptr;

	switch (node->getTag()) {

	case SprTag::SLAVE_TRAIDER:
	case SprTag::CITIZEN:
	case SprTag::BUILDER:
	case SprTag::WARRIOR:
	case SprTag::WORKER:

		break;

	case SprTag::MINE:
	case SprTag::TOWER:
	case SprTag::CASTLE:
	case SprTag::WALL:
		break;
	}

	return objToAttack;
}
