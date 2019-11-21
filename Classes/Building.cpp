#include "Building.h"
#include "Tower.h"
#include "Wall.h"
#include "Castle.h"
#include "Mine.h"
#include "Data.h"
#include "Enviroment.h"

void Building::pay(int& sum) {
	int price{0};



	if (Tower* t = dynamic_cast<Tower*>(this))			//���� �� ��'��� � ������
	{
		if (towerLevelsPrices.size() > level) {
			price = towerLevelsPrices[level + 1];
			nextUpgradeDuration = towerTimeBuilding[level + 1];
		}
	}
	else if (Wall* w = dynamic_cast<Wall*>(this))		//���� �� ��'��� � �����
	{
		if (wallLevelsPrices.size() > level) {
			price = wallLevelsPrices[level + 1];
			nextUpgradeDuration = wallTimeBuilding[level + 1];
		}
	}
	else if (Castle* c = dynamic_cast<Castle*>(this))	//���� �� ��'��� � ������
	{
		if (castleLevelsPrices.size() > level) {
			price = castleLevelsPrices[level + 1];
			nextUpgradeDuration = castleTimeBuilding[level + 1];
		}
	}
	else if (Mine* m = dynamic_cast<Mine*>(this))		//���� �� ��'��� � ������
	{
		if (mineLevelsPrices.size() > level) {
			price = mineLevelsPrices[level + 1];
			nextUpgradeDuration = mineTimeBuilding[level + 1];
		}
	}

	if (price < sum && price!=0) {
		sum -= price;
		upgrade();
	}
}


int Building::getLevel() {
	return level;
}

void Building::increaseLevel() {
	level++;
}

void Building::upgrade() {
	isBuilding = true;
	increaseLevel();
	timeDependedAction();
	GameTime::addTimeDependedObject(-1, this);

	// spr->setTexture()				���������� ���� �������� ������� �����
}




void Building::timeDependedAction()
{
	if(currentState>=nextUpgradeDuration)
	{
		GameTime::removeTimeDependedObject(this);
	}

	currentState++;
}