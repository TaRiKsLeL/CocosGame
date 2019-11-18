#include "CitizenController.h"

CitizenController* CitizenController::citizenController{ nullptr };

CitizenController::CitizenController() {
}

CitizenController* CitizenController::getInstance() {
	if (citizenController)
		return citizenController;

	citizenController = new CitizenController();
	return citizenController;
}