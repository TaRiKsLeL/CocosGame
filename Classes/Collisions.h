#pragma once
#include "Player.h"
#include "BuilderController.h"
#include "BuildingController.h"
#include "CitizenController.h"
#include "WarriorController.h"
#include "WorkerController.h"
#include "EnemyController.h"


class Collisions
{
public:

	bool onPlayerContactBegin(PhysicsContact&);
	bool onPlayerContactSeparate(PhysicsContact&);


};

