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

class BuildingController : public ITimeDepended {
private:

	static BuildingController* buildingController;


	Castle* castle;
	
	queue<Mine*> minesSearchingWorkers;


	vector<Mine*> mines;
	vector<Tower*> towers;
	vector<Wall*> walls;

	void createWall(Direction,int);
	void createTower(Direction,int);
	void createMine(int);

	void createCenteralBuildings(float,int);
	void generateBuildings(int, int, int);

public:


	BuildingController();

	Building* findBuildingByTagAndPosition(int,Vec2);

	KingdomBorders* getKingdomBorders();

	Wall* findWallByPos(Vec2);
	Castle* getCastle();

	Vec2 getCastlePos();

	static BuildingController* getInstance();

	void enableBuildings();

	queue <Mine*> *getMinesSearchingWorkers();

	void timeDependedAction() override;
};