#include "Tower.h"



Tower::Tower(bool dir, const vector<std::string>* images) : Building(images) {

	spr->setTag(SprTag::TOWER);

	if (dir) {
		direction.right = dir;
		spr->setFlipX(-1);
	}
	else {
		direction.left = dir;
	}
}

void Tower::pay(int& sum) {
	int price{ 0 };

	if (levelsImages->size()-1 > level) {
		price = towerLevelsPrices[level + 1];
		nextUpgradeDuration = towerTimeBuilding[level + 1];

		if (price <= sum && price != 0) {
			sum -= price;
			log("Sum after buying TOWER %d", sum);
			upgrade();
		}
	}

	
}