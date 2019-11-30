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

Worker* WorkerController::findClosest(Vec2 pos)
{
	vector<Worker*>* workers = controller.getElems();

	Vec2 closest = Vec2(INT32_MAX, INT32_MAX);

	for (Worker* tmp : *workers) {
		if (abs(pos.x - closest.x) > abs(pos.x - tmp->getPosition().x) &&tmp)
			closest = tmp->getPosition();
	}

	return findByPosition(closest);
}

Worker* WorkerController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}

bool WorkerController::setPositionToWork(Vec2 pos)
{
	Worker* worker = findClosest(pos);

	if (worker) {
		worker->stopMoving();
		worker->moveStart(pos);
		return true;
	}

	return false;
}

queue<Worker*>* WorkerController::getWorkersToPutInsideMine()
{
	return &workersToPutInsideMine;
}

void WorkerController::timeDependedAction()
{
	while (workersToPutInsideMine.size() > 0) {
		Worker* worker = workersToPutInsideMine.front();
		deleteByPos(worker->getPosition());
		workersToPutInsideMine.pop();
	}

	if (workersToPutInsideMine.size() == 0)
		GameTime::removeTimeDependedObject(this);
	
}
