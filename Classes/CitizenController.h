#pragma once
#include "NPCController.h"
#include "cocos2d.h"
#include "Citizen.h"
#include <vector>

USING_NS_CC;

class CitizenController
{

private:
	CitizenController();
	static CitizenController* citizenController;
public:

	static CitizenController* getInstance();

};
