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




Citizen::Citizen(Vec2 pos) : FriendlyNPC(pos, CITIZEN_SPR) {}