#include "WarriorController.h"

WarriorController* WarriorController::warriorController{ nullptr };

WarriorController::WarriorController() {
	warriors = new std::vector<Warrior*>();
}

WarriorController* WarriorController::getInstance() {
	if (warriorController)
		return warriorController;

	warriorController = new WarriorController();
	return warriorController;

}

void WarriorController::create(Vec2 pos) {

	warriors->push_back(new Warrior(pos));
}

void WarriorController::allMoveRand() {
	for (Warrior* tmp : *warriors) {
		GameTime::addMoveableObject(tmp);
	}
}

Warrior* WarriorController::findByPosition(Vec2 pos) {

	for (Warrior* tmp : *warriors) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}

Warrior* WarriorController::findClosestFree(Vec2 pos) {

	for (Warrior* tmp : *warriors) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}