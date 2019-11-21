#include <BuildingController.h>
#include "Data.h"

BuildingController* BuildingController::buildingController{nullptr};


BuildingController::BuildingController() {
	log("init castle");
	castle = new Castle();
	//createWalls();

	buildingController = this;
}

void BuildingController::createWalls() {
	for (int i = 0; i < 4; i++) {

		log("Init walls");

		Wall* wall = new Wall();
		walls->push_back(wall);
	}
}


BuildingController* BuildingController::getInstance() {
	if (buildingController) {
		return buildingController;
	}
	buildingController = new BuildingController();
	return buildingController;
}