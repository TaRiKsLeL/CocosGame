#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Worker.h"
#include "BaseController.h"

#include "UI.h"

USING_NS_CC;


class WorkerController
{

private:
	BaseController<Worker> controller;
	WorkerController();
	static WorkerController* workerController;
public:

	static WorkerController* getInstance();
	void create(Vec2);
	void allMoveRand();
	void deleteByPos(Vec2);
	Worker* findByPosition(Vec2);
};
