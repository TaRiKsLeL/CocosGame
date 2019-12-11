#include "CitizenController.h"
#include "AnimationCreator.h"


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
	controller.deleteByPos(pos);

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

void CitizenController::setNewRole(SprTag tag, Payable* citzenPayable) {
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

Citizen::Citizen(Vec2 pos) : FriendlyNPC(pos) { 
	isPayed = false;
	spr->getPhysicsBody()->setCategoryBitmask(CITIZEN_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(CITIZEN_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(CITIZEN_COLLIDE_BM);

	spr->setTag(SprTag::CITIZEN);

	animWalk = AnimationCreator::getInstance()->createAnimate
	(
		CITIZEN_WALK_FRAMES,
		CITIZEN_WALK_IMAGES_AMOUNT,
		CITIZEN_WALK_IMAGE_WIDTH,
		CITIZEN_WALK_IMAGE_HEIGHT,
		CITIZEN_WALK_TIME_PER_FRAME
	);
	spr->runAction(animWalk);
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