#include "BuilderController.h"

BuilderController* BuilderController::builderController{ nullptr };

BuilderController::BuilderController() {
	
}

BuilderController* BuilderController::getInstance() {
	if (builderController)
		return builderController;

	builderController = new BuilderController();
	return builderController;

}

void BuilderController::create(Vec2 pos) {
	controller.create(pos);
}

void BuilderController::allMoveRand() {
	controller.allMoveRand();
}

void BuilderController::deleteByPos(Vec2 pos) {
	Enviroment::getInstance()->getScene()->removeChild(controller.deleteByPos(pos)->getSpr(), true);
}

Builder* BuilderController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}

Builder* BuilderController::findClosestFree(Vec2 pos) {

	

	return nullptr;
}