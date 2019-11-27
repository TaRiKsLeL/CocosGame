#include "GameScene.h"

/*
=====================================================================================================
onContact
=====================================================================================================
*/

bool GameScene::onPlayerContactBegin(PhysicsContact& contact)
{
	Player* player = nullptr;

	log("collision %d", count);
	count++;

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
bool GameScene::onPlayerContactBegin(PhysicsContact& contact)
{

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	Player* player = nullptr;
	SlaveTraider* slaveTraider = nullptr;
	Citizen* citizen = nullptr;
	Building* building = nullptr;

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
		else if (nodeB->getTag() == SprTag::CITIZEN)
			citizen = CitizenController::getInstance()->findByPosition(nodeB->getPosition());



		building = BuildingController::getInstance()->findBuildingByTagAndPosition(nodeA->getTag(), nodeA->getPosition());

		if (!building) {
			building = BuildingController::getInstance()->findBuildingByTagAndPosition(nodeB->getTag(), nodeB->getPosition());
		}


		if (player != nullptr)
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
			else if (player && building) {
				log("%d", player->getMoney());

				log("building pay");

				if (Enviroment::getInstance()->getBorders()->isInKingdom(building->getSprite()->getPositionX())) {
					player->setPayable(building);
				}
				else if (Wall* wall = dynamic_cast<Wall*>(building)) {
					player->setPayable(building);
					Enviroment::getInstance()->setBorders(BuildingController::getInstance()->getKingdomBorders());
				}

			}

	}

	return true;
}
*/

/*
=====================================================================================================
onContactSeparate
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
		objToPay = dynamic_cast<IPayable*>(building);
		break;
	}
	return objToPay;
}
