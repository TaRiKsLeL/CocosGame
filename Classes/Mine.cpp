#include "Mine.h"

Mine::Mine(const vector<std::string>* images) : Building(images){
	spr->setTag(SprTag::MINE);
	
	spr->setPhysicsBody(createPhysBody());


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

PhysicsBody* Mine::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);

	pb->setContactTestBitmask(MINE_COLLIDE_BM);
	pb->setCategoryBitmask(MINE_CATEGORY_BM);
	pb->setCollisionBitmask(MINE_COLLIDE_BM);
	
	pb->setDynamic(false);

	return pb;
}

void Mine::addWorker()
{
	amInside++;
}

int Mine::workersAmountInside()
{
	return amInside;
}
