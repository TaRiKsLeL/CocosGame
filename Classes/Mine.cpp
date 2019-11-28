#include "Mine.h"

Mine::Mine(const vector<std::string>* images) : Building(images){
	spr->setTag(SprTag::MINE);
}

void Mine::pay(int& sum) {
	int price{ 0 };

	if (levelsImages->size()-1 > level) {
		price = mineLevelsPrices[level + 1];
		nextUpgradeDuration = mineTimeBuilding[level + 1];

		if (price <= sum && price != 0) {
			sum -= price;
			upgrade();
		}
	}

	
}