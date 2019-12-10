#include "WarriorController.h"

WarriorController* WarriorController::warriorController{ nullptr };

WarriorController::WarriorController() : m_areFree(true) {
	GameTime::addTimeDependedObject(-1, this);
}

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

Warrior* WarriorController::findByNode(Node* node) {
	for (Warrior* tmp : *(controller.getElems()))
	{
		if (tmp->getNode() == node)
			return tmp;
	}
	return nullptr;
}

void WarriorController::moveToWall() {
	int leftBorder = Enviroment::getInstance()->getBorders()->leftX;
	int rightBorder = Enviroment::getInstance()->getBorders()->rightX;

	int leftCount = 0;
	int rightCount = 0;

	Vec2 leftDiapason;
	Vec2 rightDiapason;

	leftDiapason.x = leftBorder + WALL_DISTANCE_TO_WARRIORS;
	leftDiapason.y = leftBorder + WALL_DISTANCE_TO_WARRIORS + WALL_DIAPASON_WARRIORS_STAND;

	rightDiapason.x = rightBorder - WALL_DISTANCE_TO_WARRIORS;
	rightDiapason.y = rightBorder - WALL_DISTANCE_TO_WARRIORS - WALL_DIAPASON_WARRIORS_STAND;

	for (Warrior* tmp : *controller.getElems()) {

		if (!tmp->isOnTower()) 
		{
			tmp->stopMoving();

			if (leftCount <= rightCount) {
				tmp->moveStart(Vec2(RandomHelper::random_int<int>(leftDiapason.x, leftDiapason.y), GENERAL_Y));
				leftCount++;
			}
			else
			{
				tmp->moveStart(Vec2(RandomHelper::random_int<int>(rightDiapason.y, rightDiapason.x), GENERAL_Y));
				rightCount++;
			}
		}
	}
}

void WarriorController::allMoveStop() {
	controller.allStopMove();
}

void WarriorController::removeTargetByTargetPosition(Vec2 pos) {
	for (Warrior* tmp : *controller.getElems()) {
		if (tmp->getTarget() != nullptr && tmp->getTarget()->getPosition().x == pos.x)
			tmp->removeTarget();
	}
}

void WarriorController::timeDependedAction() {
	if (EnemyController::getInstance()->enemiesAreAlive()) {
		m_areFree = false;
		moveToWall();
	}
	else {
		if (m_areFree == false) {
			m_areFree = true;
			allMoveStop();
			allMoveRand();
			GameTime::removeTimeDependedObject(this);
		}
	}
}

bool WarriorController::areFree() {
	return m_areFree;
}
