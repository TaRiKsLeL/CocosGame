#include "GameScene.h"

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

	IPayable* objToPay = nullptr;

	switch (nonPlayerNode->getTag()) {

	case SprTag::SLAVE_TRAIDER:
		slaveTraider = SlaveTraider::getInstance();
		objToPay = dynamic_cast<IPayable*>(slaveTraider);
		break;
	case SprTag::CITIZEN:
		citizen = CitizenController::getInstance()->findByPosition(nonPlayerNode->getPosition());
		objToPay = dynamic_cast<IPayable*>(citizen);
		break;
	case SprTag::BUILDER:
		builder = BuilderController::getInstance()->findByPosition(nonPlayerNode->getPosition());
		objToPay = dynamic_cast<IPayable*>(builder);
		break;
	case SprTag::WARRIOR:
		warrior = WarriorController::getInstance()->findByPosition(nonPlayerNode->getPosition());
		objToPay = dynamic_cast<IPayable*>(warrior);
		break;
	case SprTag::WORKER:

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
		builder = BuilderController::getInstance()->findByPosition(nodeA->getPosition());
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

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();



	return true;
}