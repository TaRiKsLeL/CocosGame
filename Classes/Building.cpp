#include "Building.h"
#include "Tower.h"
#include "Wall.h"
#include "Castle.h"
#include "Mine.h"
#include "Data.h"
#include "Enviroment.h"

/*
=====================================================================================================
CONSTRUCTORS
=====================================================================================================
*/

Building::Building(std::string fileName,const int width, const int height)
{
	this->filename = fileName;
	buildingWigth = width;
	buildingHeight = height;
	//level = 0;

	spr = Sprite::create(fileName);
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));

	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

Building::Building(const vector<std::string>* images) {

	nextUpgradeDuration = 10;

	levelsImages = images;
	
	spr = Sprite::create(levelsImages->at(level));
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));
	spr->addComponent(createPhysBody());
		
	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

/*
=====================================================================================================
INTERACTION
=====================================================================================================
*/

PhysicsBody* Building::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	pb->setContactTestBitmask(true);
	pb->setCategoryBitmask(BUILDING_CATEGORY_BM);
	pb->setCollisionBitmask(BUILDING_COLLIDE_BM);
	return pb;
}


void Building::upgrade() {
	isBuilding = true;
	level++;
	//GameTime::addTimeDependedObject(-1, this);

	log("%d", level);

	spr->setTexture(levelsImages->at(level));
	spr->getTexture()->setAliasTexParameters();
	spr->removeAllComponents();
	spr->addComponent(createPhysBody());
}


void Building::timeDependedAction()
{
	if (currentState > nextUpgradeDuration)
	{
		GameTime::removeTimeDependedObject(this);
	}

	currentState++;
}

int Building::getLevel() {
	return level;
}

Sprite* Building::getSprite() {
	return spr;
}