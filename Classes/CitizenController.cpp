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



Citizen::Citizen() {}

Citizen::Citizen(Vec2 pos) {
	spr = Sprite::create(CITIZEN);
	spr->setPosition(pos);
	spr->setAnchorPoint(Vec2(0, 0));
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);
}