#include "Wall.h"


Wall::Wall(bool dir,const vector<std::string> *images) : Building(images) , m_HP(0) {

	spr->setTag(SprTag::WALL);
	
	spr->addComponent(createPhysBody());
	
	if (dir) {
		direction.right = dir;
		spr->setFlipX(-1);
	}
	else {
		direction.left = dir;
	}
}

PhysicsBody* Wall::createPhysBody() {
	spr->removeAllComponents();

	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	pb->setContactTestBitmask(WALL_COLLIDE_BM);
	pb->setCategoryBitmask(WALL_CATEGORY_BM);
	pb->setCollisionBitmask(WALL_COLLIDE_BM);
	return pb;
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


/*
=====================================================================================================
WALL attacked
=====================================================================================================
*/


void Wall::hit(int attPower) {
	m_HP -= attPower;
}

bool Wall::canBeAttacked() {
	if(m_HP > 0)
		return true;
	return false;
}

/*
=====================================================================================================
get/set
=====================================================================================================
*/

void Wall::setHP(int hp) {
	m_HP = hp;
}
