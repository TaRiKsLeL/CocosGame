#include "Tower.h"



Tower::Tower(Direction dir, const vector<std::string>* images) : Building(images), maxWarriorNum(towerMaxWarriors.at(0)) {

	spr->setTag(SprTag::TOWER);
	
	spr->setPhysicsBody(createPhysBody());

	
	if (dir == Direction::RIGHT) {
		direction = dir;
		spr->setFlipX(-1);
	}
	else {
		direction = dir;
	}
}

void Tower::pay(int& sum) {
	int price{ 0 };

	if (levelsImages->size()-1 > level) {
		price = towerLevelsPrices[level + 1];
		nextUpgradeDuration = towerTimeBuilding[level + 1];

		if (price <= sum && price != 0) {
			sum -= price;
			upgrade();
		}
	}

	
}

PhysicsBody* Tower::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);

	pb->setContactTestBitmask(TOWER_COLLIDE_BM);
	pb->setCategoryBitmask(TOWER_CATEGORY_BM);
	pb->setCollisionBitmask(TOWER_COLLIDE_BM);

	return pb;
}

void Tower::specitalUpdateAction() {
	int counter = 0;
	
	maxWarriorNum = towerMaxWarriors.at(level);

	for (Warrior* tmp : warriorsInsideTower) {
		tmp->setFixedPosition(this->getPosition() + towerSetWariorShift.at(level).at(counter));
			counter++;
	}
}


void Tower::addWarrior(Warrior* sprite) {
	if (warriorsInsideTower.size() < maxWarriorNum) {
		sprite->setFixedPosition(this->getPosition() + towerSetWariorShift.at(level).at(warriorsInsideTower.size()));
		sprite->setSprDirection(direction);
		warriorsInsideTower.push_back(sprite);
	}
}

bool Tower::canAddWarrior() {
	return warriorsInsideTower.size() < maxWarriorNum;
}
