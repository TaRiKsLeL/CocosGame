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

	EventListenerPhysicsContact* workerContactListener = EventListenerPhysicsContact::create();
	workerContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onWorkerContactBegin, this);
	//workerContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onWorkerContactSeparate, this);

	EventListenerPhysicsContact* enemyContactListener = EventListenerPhysicsContact::create();
	enemyContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onEnemyContactBegin, this);

	EventListenerPhysicsContact* shooterRangeContactListener = EventListenerPhysicsContact::create();
	shooterRangeContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onShooterRangeContactBegin, this);
	shooterRangeContactListener->onContactSeparate = CC_CALLBACK_1(GameScene::GameScene::onShooterRangeContactSeparate, this);

	EventListenerPhysicsContact* arrowListener = EventListenerPhysicsContact::create();
	arrowListener->onContactBegin = CC_CALLBACK_1(GameScene::onArrowContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(playerContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(builderContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(workerContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(enemyContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(shooterRangeContactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(arrowListener, this);

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
	
	if (payable != nullptr) {
		log("plyer payable");
		player->setPayable(payable);
	}
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

	if (player != nullptr && player->focused()) {
		if (player->checkFocusedObj(payable))
			player->disableFocusBuyListener();
	}


	return true;
}



IPayable* GameScene::getPayableByNode(Node* nonPlayerNode) {

	Building* building = nullptr;

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

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() & BUILDER_CATEGORY_BM) == BUILDER_CATEGORY_BM) {
		builder = BuilderController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() & BUILDER_CATEGORY_BM) == BUILDER_CATEGORY_BM) {
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

	if (builder && builder->isMovingToBuilding() && builder->getCurrentPointMoveTo() == building->getPosition()) {
		builder->stopMoving();
		builder->setMovingToBuild(false);
		builder->setBuild(true);
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

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() & BUILDER_CATEGORY_BM) == BUILDER_CATEGORY_BM) {
		builder = BuilderController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() & BUILDER_CATEGORY_BM) == BUILDER_CATEGORY_BM) {
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
		builder->moveRandStart();
		builder->setBuild(false);
	//	building->setBuildingStatus(false);
		return true;
	}

	return false;
}

bool GameScene::onWorkerContactBegin(PhysicsContact& contact)
{
	Worker* worker = nullptr;
	Mine* mine = nullptr;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Node* secondNode = nullptr;

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() & WORKER_CATEGORY_BM) == WORKER_CATEGORY_BM) {
		worker = WorkerController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() & WORKER_CATEGORY_BM) == WORKER_CATEGORY_BM) {
		worker = WorkerController::getInstance()->findByPosition(nodeB->getPosition());
		secondNode = nodeA;
	}
	else
		return false;

	if ((secondNode->getPhysicsBody()->getCollisionBitmask() & WORKER_COLLIDE_BM) == 0)
		return false;

	switch (secondNode->getTag()) {
	case SprTag::MINE:
		Building * building = BuildingController::getInstance()->findBuildingByTagAndPosition(secondNode->getTag(), secondNode->getPosition());
		
		if (building == nullptr) return false;
		
		mine = dynamic_cast<Mine*>(building);


		if (worker && worker->getCurrentPointMoveTo() == building->getPosition()) {
			worker->stopMoving();
			mine->addWorker();
			//WorkerController::getInstance()->deleteByPos(worker->getPosition());
			log("In mine: %d", mine->workersAmountInside());
			WorkerController::getInstance()->getWorkersToPutInsideMine()->push(worker);
			GameTime::addTimeDependedObject(-1, WorkerController::getInstance());

			//building->setBuildingStatus(true);
			return true;
		}

		break;
	}



	return false;
}

bool GameScene::onWarriorContactBegin(PhysicsContact& contact)
{
	Warrior* warrior = nullptr;
	Tower* tower = nullptr;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Node* secondNode = nullptr;

	if ((nodeA->getPhysicsBody()->getCategoryBitmask() & WARRIOR_CATEGORY_BM) == WARRIOR_CATEGORY_BM) {
		warrior = WarriorController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() & WARRIOR_CATEGORY_BM) == WARRIOR_CATEGORY_BM) {
		warrior = WarriorController::getInstance()->findByPosition(nodeB->getPosition());
		secondNode = nodeA;
	}
	else
		return false;

	if ((secondNode->getPhysicsBody()->getCollisionBitmask() & WARRIOR_COLLIDE_BM) == 0)
		return false;

	switch (secondNode->getTag()) {

	case SprTag::TOWER:
		Building* building = BuildingController::getInstance()->findBuildingByTagAndPosition(secondNode->getTag(), secondNode->getPosition());
		if (building == nullptr) return false;
		
		tower = dynamic_cast<Tower*>(building);
		
		break;
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

/*
=====================================================================================================
onContact shoot
=====================================================================================================
*/

bool GameScene::onShooterRangeContactBegin(PhysicsContact& contact)
{
	Warrior* shooter = nullptr;
	Node* secondNode = nullptr;



	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ SHOOTER_CATEGORY_BM) == 0 ) {
		shooter = WarriorController::getInstance()->findByNode(nodeA);
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ SHOOTER_CATEGORY_BM) == 0) {
		shooter = WarriorController::getInstance()->findByNode(nodeB);
		secondNode = nodeA;
	}
	else
		return false;


	
	shooter->setTarget(secondNode);
	
	return true;
}

bool GameScene::onShooterRangeContactSeparate(PhysicsContact& contact)
{
	Warrior* shooter = nullptr;
	Node* secondNode = nullptr;




	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ SHOOTER_CATEGORY_BM) == 0) {
		shooter = WarriorController::getInstance()->findByNode(nodeA);
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ SHOOTER_CATEGORY_BM) == 0) {
		shooter = WarriorController::getInstance()->findByNode(nodeB);
		secondNode = nodeA;
	}
	else
		return false;

	shooter->removeTarget();

	return true;
}


/*
=====================================================================================================
onContact shoot
=====================================================================================================
*/

bool GameScene::onArrowContactBegin(PhysicsContact& contact)
{
	Enemy* enemy = nullptr;
	Node* secondNode = nullptr;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if ((nodeA->getPhysicsBody()->getCategoryBitmask() ^ ARROW_CATEGORY_BM) == 0) {
		enemy = EnemyController::getInstance()->findByPosition(nodeA->getPosition());
		secondNode = nodeB;
	}
	else if ((nodeB->getPhysicsBody()->getCategoryBitmask() ^ ARROW_CATEGORY_BM) == 0) {
		enemy = EnemyController::getInstance()->findByPosition(nodeB->getPosition());
		secondNode = nodeA;
	}
	else
		return false;

	if ((secondNode->getPhysicsBody()->getCollisionBitmask() & ARROW_COLLIDE_BM) == 0)
		return false;

	secondNode->removeFromParentAndCleanup(true);
	EnemyController::getInstance()->deleteByPos(enemy->getPosition());


	return false;
}
