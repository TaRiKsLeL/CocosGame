#include "CitizenController.h"


/*
=====================================================================================================
Controller
=====================================================================================================
*/

CitizenController* CitizenController::citizenController{ nullptr };

CitizenController::CitizenController() {
}




CitizenController* CitizenController::getInstance() {
	if (citizenController)
		return citizenController;

	citizenController = new CitizenController();
	return citizenController;

}

void CitizenController::deleteByPos(Vec2 pos) {
	Enviroment::getInstance()->getScene()->removeChild(controller.deleteByPos(pos)->getSpr(), true);

}

void CitizenController::create(Vec2 pos) {
	controller.create(pos);
}

void CitizenController::allMoveRand() {
	controller.allMoveRand();
}

Citizen* CitizenController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}

void CitizenController::setNewRole(SprTag tag, IPayable* citzenPayable) {
	Citizen* citizenToChange = dynamic_cast<Citizen*>(citzenPayable);


	switch (tag) {
	case SprTag::BUILDER:
		BuilderController::getInstance()->create(citizenToChange->getPosition());
		break;
	case SprTag::WARRIOR:
		WarriorController::getInstance()->create(citizenToChange->getPosition());
		break;
	case SprTag::WORKER:
		WorkerController::getInstance()->create(citizenToChange->getPosition());
		break;
	}

	deleteByPos(citizenToChange->getPosition());

}

/*
=====================================================================================================
Citizen
=====================================================================================================
*/

Citizen::Citizen(Vec2 pos) : FriendlyNPC(pos, CITIZEN_SPR) { 
	isPayed = false;
	spr->getPhysicsBody()->setCategoryBitmask(NPC_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(NPC_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(NPC_COLLIDE_BM);

	spr->setTag(SprTag::CITIZEN);
}




void Citizen::pay(int &money) {
	if (money >= SET_ROLE_PRICE) {
		money -= SET_ROLE_PRICE;
		
		isPayed = true;
		UI::getInstance()->addCitizenSelectIcons(this);
		

		Player::getInstance()->disableBuyListener();
		Player::getInstance()->enableChoseRoleListener();


		this->stopMoving();
	}
}


void Citizen::onChangeFocus(){
	if(isPayed)
		UI::getInstance()->removeCitizenSelectIcons();
	
	this->moveRandStart();
	
}