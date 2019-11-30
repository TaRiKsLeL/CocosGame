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
	controller.deleteByPos(pos);
}

Builder* BuilderController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}

bool BuilderController::setPositionToBuild(Vec2 pos)
{
	Builder* builder = findCosestFree(pos);
	
	if (builder) {
		builder->stopMoving();
		builder->setMovingToBuild(true);
		builder->moveStart(pos);
		return true;
	}

	return false;
}

Builder* BuilderController::findCosestFree(Vec2 pos) {
	
	vector<Builder*>* builders = controller.getElems();
	
	Vec2 closest = Vec2(INT32_MAX, INT32_MAX);
	
	for (Builder* tmp : *builders) {
			if (abs(pos.x - closest.x) > abs(pos.x - tmp->getPosition().x) && !(tmp->isBuilding()) && !(tmp->isMovingToBuilding())) {
				for (int i = 0; i < TAG_COUNT; i++) {
					Building* building = BuildingController::getInstance()->findBuildingByTagAndPosition(i, pos);
					if (building != nullptr)
						if (building->getSprite()->getBoundingBox().intersectsRect(tmp->getBoundingBox())) {
							Vec2 tmpPos = tmp->getPosition();
							deleteByPos(tmpPos);
							create(tmpPos);
							return findByPosition(tmpPos);
						}
				}
				closest = tmp->getPosition();
			
		}
	}

	return findByPosition(closest);

}

Builder* BuilderController::findByDestinationPoint(Vec2 pos) {
	vector<Builder*>* builders = controller.getElems();

	for (Builder* tmp : *builders) {
		if (tmp->getCurrentPointMoveTo() == pos) {
			return tmp;
		}
	}

	return nullptr;
}