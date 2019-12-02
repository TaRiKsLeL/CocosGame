#include <BuildingController.h>

BuildingController* BuildingController::buildingController{nullptr};


BuildingController::BuildingController() {
	
	generateBuildings(TOWERS_AMOUNT,WALLS_AMOUNT,MINES_AMOUNT);
	buildingController = this;
}


void BuildingController::generateBuildings(int towerAm,int wallsAm,int minesAm) {

	srand(time(0));

	float grountWidth = Enviroment::getInstance()->getGroundWidth();
	float center = grountWidth / 2;

	float shift =  MAX_BUILDING_WIDTH+SPACING;

	createCenteralBuildings(center, shift);

	float leftShift=shift;
	float rightShift=shift;


	int prevLeftBuild = -1;
	int prevRightBuild = -1;

	int counterOfEndless = 0;

	while (towerAm!=0 || wallsAm!=0 || minesAm!=0) {

		int random;

		counterOfEndless++;

		for (int d = 1; d <= 2; d++) 
		{														// d=1 ліва сторона, d=2 права сторона
			int buildingLeft = 0 + rand() % 3;
			int buildingRight = 0 + rand() % 3;

			random = rand() % RANDOM_FACTOR;
			
			if(d==1)
			{

				if (buildingLeft == 0 && towerAm > 0 && (prevLeftBuild != buildingLeft)) {
					leftShift += shift + random;
					createTower(false,center - leftShift);

					log("Prev duilding %d .... This building %d ", prevLeftBuild, buildingLeft);
					prevLeftBuild = buildingLeft;

					log("Adding left tower");
					counterOfEndless = 0;
					towerAm--;
				}
				else if (buildingLeft == 1 && wallsAm > 0 &&( prevLeftBuild != buildingLeft)) {
					leftShift += shift + random;
					createWall(false,center - leftShift);

					log("Prev duilding %d .... This building %d ", prevLeftBuild, buildingLeft);

					prevLeftBuild = buildingLeft;
					log("Adding left wall");
					counterOfEndless = 0;
					wallsAm--;
				}
				else if (buildingLeft == 2 && minesAm > 0 &&( prevLeftBuild != buildingLeft)) {
					leftShift += shift + random;
					createMine(center - leftShift);

					log("Prev duilding %d .... This building %d ", prevLeftBuild, buildingLeft);

					prevLeftBuild = buildingLeft;
					log("Adding left mine");
					counterOfEndless = 0;
					minesAm--;
				}
			}
			else {
				
				if (buildingRight == 0 && towerAm > 0 && (prevRightBuild != buildingRight)) {
					rightShift += shift + random;
					createTower(true,center + rightShift);

					log("Prev duilding %d .... This building %d ", prevRightBuild, buildingRight);

					prevRightBuild = buildingRight;
					log("Adding right tower");
					counterOfEndless = 0;
					towerAm--;

				}
				else if (buildingRight == 1 && wallsAm > 0 && (prevRightBuild != buildingRight)) {
					rightShift += shift + random;
					createWall(true,center + rightShift);

					log("Prev duilding %d .... This building %d ", prevRightBuild, buildingRight);

					prevRightBuild = buildingRight;
					log("Adding right wall");
					counterOfEndless = 0;
					wallsAm--;
				}
				else if (buildingRight == 2 && minesAm > 0 && (prevRightBuild != buildingRight)) {
					rightShift += shift + random;
					createMine(center + rightShift);

					log("Prev duilding %d .... This building %d ", prevRightBuild, buildingRight);

					prevRightBuild = buildingRight;
					log("Adding right mine");
					counterOfEndless = 0;
					minesAm--;
				}
			}

		}

		if (counterOfEndless == 15) {
			break;
		}
	}


}

void BuildingController::createWall(bool dir,int xPos) {
	Wall* wall = new Wall(dir,&WALLS);
	wall->getSprite()->setPosition(Vec2(xPos, GENERAL_Y));
	walls.push_back(wall);
}

void BuildingController::createTower(bool dir,int xPos) {
	Tower* tower = new Tower(dir,&TOWERS);
	tower->getSprite()->setPosition(Vec2(xPos, GENERAL_Y));
	towers.push_back(tower);
}

void BuildingController::createMine(int xPos) {
	Mine* mine = new Mine(&MINES);
	mine->getSprite()->setPosition(Vec2(xPos, GENERAL_Y));
	mines.push_back(mine);
}

void BuildingController::createCenteralBuildings(float center, int shift) {

	castle = new Castle(&CASTLES);
	castle->getSprite()->setPosition(Vec2(center, GENERAL_Y));

	for (int d = 1; d <= 2; d++) { // d=1 ліва сторона, d=2 права сторона
		if (d == 1)
		{
			Tower* tower = new Tower(false,&TOWERS);
			tower->getSprite()->setPosition(Vec2(center - shift, GENERAL_Y));


			Wall* wall = new Wall(false, &WALLS);
			wall->getSprite()->setPosition(Vec2(center - shift - 300, GENERAL_Y));

			towers.push_back(tower);
			walls.push_back(wall);

		}
		else {


			Tower* tower = new Tower(true, &TOWERS);
			tower->getSprite()->setPosition(Vec2(center + shift, GENERAL_Y));

			Wall* wall = new Wall(true, &WALLS);
			wall->getSprite()->setPosition(Vec2(center + shift + 300, GENERAL_Y));

			towers.push_back(tower);
			walls.push_back(wall);
		}
	}
}


KingdomBorders* BuildingController::getKingdomBorders() {

	float min = walls.at(0)->getSprite()->getPositionX();
	float max = walls.at(1)->getSprite()->getPositionX();

	for each (Wall* wall in walls)
	{
		if (wall->getLevel() > 0) {
			if (min > wall->getSprite()->getPositionX()) {
				min = wall->getSprite()->getPositionX();
			}

			if (max < wall->getSprite()->getPositionX()) {
				max = wall->getSprite()->getPositionX();
			}
		}
	}
	
	log("Left %f   Right %f", min, max);

	KingdomBorders *borders = new KingdomBorders();
	borders->leftX = min;
	borders->rightX = max;
	return borders;
}

Building* BuildingController::findBuildingByTagAndPosition(int tag,Vec2 position) {
	switch (tag)
	{
	case CASTLE:
		if (castle->getSprite()->getPosition().equals(position))
			return castle;
		break;
	case TOWER:
		for each (Tower* tower in towers)
			if (tower->getSprite()->getPosition().equals(position))
				return tower;
		break;
	case WALL:
		for each (Wall * wall in walls)
			if (wall->getSprite()->getPosition().equals(position))
				return wall;
		break;
	case MINE:
		for each (Mine * mine in mines)
			if (mine->getSprite()->getPosition().equals(position))
				return mine;
		break;
	default:
		return nullptr;
		break;
	}
}

BuildingController* BuildingController::getInstance() {
	if (buildingController) {
		return buildingController;
	}
	buildingController = new BuildingController();
	return buildingController;
}

queue<Mine*>* BuildingController::getMinesSearchingWorkers()
{
	return &minesSearchingWorkers;
}

void BuildingController::timeDependedAction()
{	
	Mine* mine = minesSearchingWorkers.front();

	if (mine) {

		if (mine->workersAmountInside() == MAX_MINE_CAPACITY)
			minesSearchingWorkers.pop();
		else {
			for (int i = 0; i < MAX_MINE_CAPACITY - mine->workersAmountInside(); i++)
				WorkerController::getInstance()->setPositionToWork(mine->getPosition());   // переробити. бо викликається лише 1 найближча
		}
	}
	if (minesSearchingWorkers.size() == 0)
		GameTime::removeTimeDependedObject(this);
}

Vec2 BuildingController::getCastlePos() {
	return castle->getPosition();
}

Wall* BuildingController::findWallByPos(Vec2 pos) {
	for (Wall* tmp : walls) {
		if (tmp->getPosition() == pos)
			return tmp;
	}
	return nullptr;
}

Castle* BuildingController::getCastle() {
	return castle;
}

