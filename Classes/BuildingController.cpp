#include <BuildingController.h>
#include "Data.h"
#include <time.h>
BuildingController* BuildingController::buildingController{nullptr};


BuildingController::BuildingController() {
	
	generateBuildings(TOWERS_AMOUNT,WALLS_AMOUNT,MINES_AMOUNT);
	buildingController = this;
}


void BuildingController::generateBuildings(int towerAm,int wallsAm,int minesAm) {

	srand(time(0));

	float grountWidth = Enviroment::getInstance()->getGroundWidth();
	float center = grountWidth / 2;

	int shift =  MAX_BUILDING_WIDTH+SPACING;

	createCenteralBuildings(center, shift);

	int k = 0;
	int leftShift=shift;
	int rightShift=shift;

	while (towerAm!=0 || wallsAm!=0 || minesAm!=0) {

		int random;

		for (int d = 1; d <= 2; d++) 
		{														// d=1 ліва сторона, d=2 права сторона
			int building = 0 + rand() % 3;
			k++;
			log("%d Building      %d", k,building);
			if(d==1)
			{
				random = -RANDOM_FACTOR + rand() % RANDOM_FACTOR;
				log("Left random %d", random);

				if (building == 0 && towerAm > 0) {
					leftShift += shift + random;
					createTower(false,center - leftShift);
					towerAm--;
				}
				else if (building == 1 && wallsAm > 0) {
					leftShift += shift + random;
					createWall(false,center - leftShift);
					wallsAm--;
				}
				else if (building == 2 && minesAm > 0) {
					leftShift += shift + random;
					createMine(center - leftShift);
					minesAm--;
				}
			}
			else {
				random = -RANDOM_FACTOR + rand() % RANDOM_FACTOR+RANDOM_FACTOR;
				log("Right random %d", random);
				if (building == 0 && towerAm > 0) {
					rightShift += shift + random;
					createTower(true,center + rightShift);
					towerAm--;

				}
				else if (building == 1 && wallsAm > 0) {
					rightShift += shift + random;
					createWall(true,center + rightShift);
					wallsAm--;
				}
				else if (building == 2 && minesAm > 0) {
					rightShift += shift + random;
					createMine(center + rightShift);
					minesAm--;
				}
			}

			//log("Left Shift %d", leftShift);
			//log("Right Shift %d", rightShift);
		}
	}
}


void BuildingController::createWall(bool dir,int xPos) {
	Wall* wall = new Wall(dir,WALLS);
	wall->getSprite()->setPosition(Vec2(xPos, GENERAL_Y_ANCHOR));
	walls.push_back(wall);
}

void BuildingController::createTower(bool dir,int xPos) {
	Tower* tower = new Tower(dir,TOWERS);
	tower->getSprite()->setPosition(Vec2(xPos, GENERAL_Y_ANCHOR));
	towers.push_back(tower);
}

void BuildingController::createMine(int xPos) {
	Mine* mine = new Mine(MINES);
	mine->getSprite()->setPosition(Vec2(xPos, GENERAL_Y_ANCHOR));
	mines.push_back(mine);
}

void BuildingController::createCenteralBuildings(float center, int shift) {

	castle = new Castle(CASTLES);
	castle->getSprite()->setPosition(Vec2(center, GENERAL_Y_ANCHOR));

	for (int d = 1; d < 3; d++) { // d=1 ліва сторона, d=2 права сторона
		if (d == 1)
		{
			Tower* tower = new Tower(TOWERS);
			tower->getSprite()->setPosition(Vec2(center - shift, GENERAL_Y_ANCHOR));


			Wall* wall = new Wall(WALLS);
			wall->getSprite()->setPosition(Vec2(center - shift - 300, GENERAL_Y_ANCHOR));

			towers.push_back(tower);
			walls.push_back(wall);

		}
		else {


			Tower* tower = new Tower(true,TOWERS);
			tower->getSprite()->setPosition(Vec2(center + shift, GENERAL_Y_ANCHOR));

			Wall* wall = new Wall(true, WALLS);
			wall->getSprite()->setPosition(Vec2(center + shift + 300, GENERAL_Y_ANCHOR));

			towers.push_back(tower);
			walls.push_back(wall);
		}
	}
}

BuildingController* BuildingController::getInstance() {
	if (buildingController) {
		return buildingController;
	}
	buildingController = new BuildingController();
	return buildingController;
}