#pragma once

#include "Building.h"
#include "Castle.h"
#include "Wall.h"
#include "Tower.h"
#include "Mine.h"

#include <vector>

using namespace std;

class BuildingController {
private:

	static BuildingController* buildingController;


	vector<Mine*>* mines;
	vector<Tower*>* towers;

	void createWalls();

	void loadBuildings();

public:

//	void addWall(Wall*);
//	void addTower(Tower*);
//	void addMine(Mine*);

	vector<Wall*>* walls;

	Castle* castle;


	BuildingController();

	static BuildingController* getInstance();

	void enableBuildings();
};