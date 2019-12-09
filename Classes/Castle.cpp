#include "Castle.h"
#include "EnemyController.h"
#include "UI.h"

Castle::Castle(const vector<std::string> *images) : Building(images) {
	spr->setTag(SprTag::CASTLE);
	spr->setPhysicsBody(createPhysBody());

}

void Castle::pay(int& sum) {
	int price{ 0 };

	if (levelsImages->size()-1 > level) {
		price = castleLevelsPrices[level + 1];
		nextUpgradeDuration = castleTimeBuilding[level + 1];

		if (price <= sum && price != 0) {
			sum -= price;

			if (level == levelsImages->size() - 2) {
				EnemyController::getInstance()->startInfinitySpawn();
			}

			upgrade();
		}
	}	
}


PhysicsBody* Castle::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	
	pb->setContactTestBitmask(WALL_COLLIDE_BM);
	pb->setCategoryBitmask(WALL_CATEGORY_BM);
	pb->setCollisionBitmask(WALL_COLLIDE_BM);

	return pb;
}

void Castle::specitalUpdateAction() {
	if (level == levelsImages->size() - 1) {
		log("victory");
		UI::getInstance()->setGameOverSprite(VICTORY_BACK_SPR);
		EnemyController::getInstance()->allStopMove();

	}
}

/*
=====================================================================================================
Castle attacked
=====================================================================================================
*/


void Castle::hit(int attPower) {
	UI::getInstance()->setGameOverSprite(GAME_OVER_BACK_SPR);
	EnemyController::getInstance()->allStopMove();
}

bool Castle::canBeAttacked() {
	return true;
}