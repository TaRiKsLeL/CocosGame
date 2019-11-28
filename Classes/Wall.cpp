#include "Wall.h"



Wall::Wall(bool dir,const vector<std::string> *images) : Building(images) {

	spr->setTag(SprTag::WALL);

	if (dir) {
		direction.right = dir;
		spr->setFlipX(-1);
	}
	else {
		direction.left = dir;
	}
}

void Wall::pay(int& sum) {
	int price{ 0 };

	if (levelsImages->size()-1 > level) {
		price = wallLevelsPrices[level + 1];
		nextUpgradeDuration = wallTimeBuilding[level + 1];

		if (price <= sum && price != 0) {
			sum -= price;
			upgrade();
		}
	}
}

void Wall::repair() {
	level = lastLevel;
}