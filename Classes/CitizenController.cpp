#include "CitizenController.h"

CitizenController* CitizenController::citizenController{ nullptr };

CitizenController::CitizenController() {
	citizens = new std::vector<Citizen*>();
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



Citizen::Citizen(Vec2 pos) : FriendlyNPC(pos, CITIZEN_SPR) { 
	spr->setTag(SprTag::CITIZEN);
	log("ya rodyvsa!!! Hello world!!!");
}


Citizen* CitizenController::findByPosition(Vec2 pos) {

	for (Citizen* tmp : *citizens) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}