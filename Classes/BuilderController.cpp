#include "BuilderController.h"

BuilderController* BuilderController::builderController{ nullptr };

BuilderController::BuilderController() {
	builders = new std::vector<Builder*>();
}

BuilderController* BuilderController::getInstance() {
	if (builderController)
		return builderController;

	builderController = new BuilderController();
	return builderController;

}

void BuilderController::create(Vec2 pos) {

	builders->push_back(new Builder(pos));
}

void BuilderController::allMoveRand() {
	for (Builder* tmp : *builders) {
		GameTime::addMoveableObject(tmp);
	}
}

Builder* BuilderController::findByPosition(Vec2 pos) {

	for (Builder* tmp : *builders) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}

Builder* BuilderController::findClosestFree(Vec2 pos) {

	for (Builder* tmp : *builders) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}