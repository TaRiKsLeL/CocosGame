#include "WarriorController.h"

WarriorController* WarriorController::warriorController{ nullptr };

WarriorController::WarriorController() {}

WarriorController* WarriorController::getInstance() {
	if (warriorController)
		return warriorController;

	warriorController = new WarriorController();
	return warriorController;

}

void WarriorController::create(Vec2 pos) {
	controller.create(pos);
}

void WarriorController::allMoveRand() {
	controller.allMoveRand();
}

void WarriorController::deleteByPos(Vec2 pos) {
	controller.deleteByPos(pos);
}

Warrior* WarriorController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}
