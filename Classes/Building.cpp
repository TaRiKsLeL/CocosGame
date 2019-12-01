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


Building::Building(const vector<std::string>* images) : waitForBuilder(false) {

	nextUpgradeDuration = 10;
	setBuildingStatus(false);

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
	
	return pb;
}



void Building::upgrade() {
		
	if (!isBuilding && !waitForBuilder && BuilderController::getInstance()->setPositionToBuild(this->getPosition())) {
		waitForBuilder = true;
		GameTime::addTimeDependedObject(-1, this);
	}
}

void Building::timeDependedAction()
{
	if (currentState > nextUpgradeDuration)
	{
		GameTime::removeTimeDependedObject(this);

		level++;

		BuilderController::getInstance()->findByDestinationPoint(getPosition())->setBuild(false);
		BuilderController::getInstance()->findByDestinationPoint(getPosition())->moveRandStart();

		spr->setTexture(levelsImages->at(level));
		spr->getTexture()->setAliasTexParameters();
		spr->removeAllComponents();
		spr->addComponent(createPhysBody());

		if (spr->getTag() == SprTag::WALL) {
			BuildingController::getInstance()->findWallByPos(spr->getPosition())->setHP(WALL_HP.at(level));
		}
		
		waitForBuilder = false;
		isBuilding = false;
		currentState = 0;

		Enviroment::getInstance()->updateEnviromentData();

		if (Mine* mine = dynamic_cast<Mine*>(this)) {
			if (BuildingController::getInstance()->getMinesSearchingWorkers()->size() == 0) {
				GameTime::removeTimeDependedObject(this);
			}
			BuildingController::getInstance()->getMinesSearchingWorkers()->push(mine);
			GameTime::addTimeDependedObject(-1, BuildingController::getInstance());
		}
	}

	if(isBuilding == true)
		currentState++;

	log("%d", currentState);
}

int Building::getLevel() {
	return level;
}

void Building::setBuildingStatus(bool status) {
	isBuilding = status;
}


Vec2 Building::getPosition() {
	return spr->getPosition();
}

Sprite* Building::getSprite() {
	return spr;
}