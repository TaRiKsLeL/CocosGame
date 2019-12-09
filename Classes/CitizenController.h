#pragma once

#include "UI.h"
#include <vector>
#include "Data.h"
#include "Player.h"
#include "Citizen.h"
#include "Enviroment.h"
#include "BuilderController.h"
#include "WorkerController.h"
#include "BaseController.h"


USING_NS_CC;


class CitizenController 
{

private:
	BaseController<Citizen> controller;
	CitizenController();
	static CitizenController* citizenController;
public:
	
	static CitizenController* getInstance();
	void create(Vec2);
	void allMoveRand();
	void setNewRole(SprTag , Payable*);
	void deleteByPos(Vec2);
	Citizen* findByPosition(Vec2);
};
