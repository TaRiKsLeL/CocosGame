#include "Castle.h"
#include "EnemyController.h"

Castle::Castle(const vector<std::string> *images) : Building(images) {
	spr->setTag(SprTag::CASTLE);
}

void Castle::pay(int& sum) {
	int price{ 0 };

	if (levelsImages->size()-1 > level) {
		price = castleLevelsPrices[level + 1];
		nextUpgradeDuration = castleTimeBuilding[level + 1];

		if (price <= sum && price != 0) {
			sum -= price;
			upgrade();
		}
	}	
}

/*
=====================================================================================================
Castle attacked
=====================================================================================================
*/


void Castle::hit(int attPower) {
	EnemyController::getInstance()->allStopMove();
	log("gg");
}

bool Castle::canBeAttacked() {
	return true;
}