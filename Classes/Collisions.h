#pragma once
#include "Player.h"
#include "BuilderController.h"
#include "BuildingController.h"
#include "CitizenController.h"
#include "WariorController.h"
#include "WorkerController.h"
#include "EnemyController.h"


class Collisions
{
public:

	static void playerCollide(Player*, Node*, Node*);

};

