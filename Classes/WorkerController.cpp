#include "WarriorController.h"

WorkerController* WorkerController::workerController{ nullptr };

WorkerController::WorkerController() {}

WorkerController* WorkerController::getInstance() {
	if (workerController)
		return workerController;

	workerController = new WorkerController();
	return workerController;

}

void WorkerController::create(Vec2 pos) {
	controller.create(pos);
}

void WorkerController::allMoveRand() {
	controller.allMoveRand();
}

void WorkerController::deleteByPos(Vec2 pos) {
	controller.deleteByPos(pos);
}

Worker* WorkerController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}
