#include "CitizenController.h"


/*
=====================================================================================================
Controller
=====================================================================================================
*/

CitizenController* CitizenController::citizenController{ nullptr };

CitizenController::CitizenController() {
	citizens = new std::vector<Citizen*>();
}

void CitizenController::deleteByPos(Vec2 pos) {
	Citizen* toDelete = findByPosition(pos);


	for (int i = 0; i < citizens->size(); i++) {
		if (citizens->at(i)->getPosition().x == pos.x) {
			citizens->erase(citizens->begin() + i);
			break;
		}
	}

	Enviroment::getInstance()->getScene()->removeChild(toDelete->getSpr(), true);

	delete toDelete;

}


CitizenController* CitizenController::getInstance() {
	if (citizenController)
		return citizenController;

	citizenController = new CitizenController();
	return citizenController;

}

void CitizenController::create(Vec2 pos) {
	
	citizens->push_back(new Citizen(pos));
}

void CitizenController::allMoveRand() {
	for (Citizen *tmp : *citizens) {
		GameTime::addMoveableObject(tmp);
	}
}

Citizen* CitizenController::findByPosition(Vec2 pos) {

	for (Citizen* tmp : *citizens) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}

void CitizenController::setNewRole(SprTag tag, IPayable* citzenPayable) {
	Citizen* citizenToChange = dynamic_cast<Citizen*>(citzenPayable);


	switch (tag) {
	case SprTag::BUILDER:
		BuilderController::getInstance()->create(citizenToChange->getPosition());
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
	spr->setTag(SprTag::CITIZEN);
	log("ya rodyvsa!!! Hello world!!!");
}




void Citizen::pay(int &money) {
	if (money >= SET_ROLE_PRICE) {
		money -= SET_ROLE_PRICE;
		
		isPayed = true;
		UI::getInstance()->addCitizenSelectIcons(this);
		

		Player::getInstance()->removeActListener();
		Player::getInstance()->setSelectRoleListener();


		this->stopMoving();
	}
}


void Citizen::onChangeFocus(){
	if(isPayed)
		UI::getInstance()->removeCitizenSelectIcons();
	
	this->moveStart();
	
}