#pragma once

#include "Enviroment.h"
#include "Building.h"
#include "Castle.h"
#include "Wall.h"
#include "Tower.h"
#include "Mine.h"
#include "Data.h"
#include <time.h>
#include <vector>
#include "KingdomBorders.h"

using namespace std;

class BuildingController {
private:

	static BuildingController* buildingController;


	Castle* castle;
	
	vector<Mine*> mines;
	vector<Tower*> towers;


	void createWall(bool,int);
	void createTower(bool,int);
	void createMine(int);

	void createCenteralBuildings(float,int);
	void generateBuildings(int, int, int);

public:

	vector<Wall*> walls;

	BuildingController();

	Building* findBuildingByTagAndPosition(int,Vec2);

	KingdomBorders* getKingdomBorders();

	void createBuilding(int& type, bool side, int& previus, int& num, int& counter, float& sideShift,float center,float shift,int random);

	static BuildingController* getInstance();

	void enableBuildings();
};