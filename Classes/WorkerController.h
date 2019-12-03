#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Worker.h"
#include "BaseController.h"
#include "UI.h"

USING_NS_CC;


class WorkerController : public ITimeDepended
{

private:
	BaseController<Worker> controller;
	WorkerController();
	static WorkerController* workerController;

	queue<Worker*> workersToPutInsideMine;

public:

	static WorkerController* getInstance();
	void create(Vec2);
	void allMoveRand();
	void deleteByPos(Vec2);
	Worker* findClosest(Vec2);
	Worker* findByPosition(Vec2);
	bool setPositionToWork(Vec2);

	queue<Worker*> *getWorkersToPutInsideMine();
	void removebyPos(Vec2);
	void timeDependedAction() override;

};
