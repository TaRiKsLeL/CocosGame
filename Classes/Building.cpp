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
	level = 0;

	spr = Sprite::create(fileName);
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));

	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

Building::Building(vector<std::string> images) {

	nextUpgradeDuration = 10;

	levelsImages = images;
	
	spr = Sprite::create(levelsImages.at(level));
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));
	spr->addComponent(createPhysBody());
	spr->setTag(SprTag::BUILDING);

	setQueryRect();

	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

/*
=====================================================================================================
INTERACTION
=====================================================================================================
*/

void Building::pay(int& sum) {
	int price{0};


	if (Tower* t = dynamic_cast<Tower*>(this))			//ÿêùî ì³é îá'ºêò º âèøêîþ
	{
		if (towerLevelsPrices.size() > level) {
			price = towerLevelsPrices[level + 1];
			nextUpgradeDuration = towerTimeBuilding[level + 1];
		}
	}
	else if (Wall* w = dynamic_cast<Wall*>(this))		//ÿêùî ì³é îá'ºêò º ñò³íîþ
	{
		if (wallLevelsPrices.size() > level) {
			price = wallLevelsPrices[level + 1];
			nextUpgradeDuration = wallTimeBuilding[level + 1];
		}
	}
	else if (Castle* c = dynamic_cast<Castle*>(this))	//ÿêùî ì³é îá'ºêò º çàìêîì
	{
		if (castleLevelsPrices.size() > level) {
			price = castleLevelsPrices[level + 1];
			nextUpgradeDuration = castleTimeBuilding[level + 1];
		}
	}
	else if (Mine* m = dynamic_cast<Mine*>(this))		//ÿêùî ì³é îá'ºêò º øàõòîþ
	{
		if (mineLevelsPrices.size() > level) {
			price = mineLevelsPrices[level + 1];
			nextUpgradeDuration = mineTimeBuilding[level + 1];
		}
	}

	if (price < sum && price!=0) {
		sum -= price;
		upgrade();
	}
}




PhysicsBody* Building::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setContactTestBitmask(true);
	pb->setDynamic(false);
	return pb;
}

void Building::setQueryRect() {

	Vec2 point(spr->getPosition().x + spr->getContentSize().width / 2,
		spr->getPosition().y + spr->getContentSize().height / 2);

	log("%f", point.x);
	log("%f", point.y);

	Enviroment::getInstance()->getScene()->getPhysicsWorld()->queryPoint(
		[=](PhysicsWorld& world, PhysicsShape& shape, void* userData)->bool
		{
			if (shape.getTag() == SprTag::PLAYER) {
				Player* player = Player::getInstance();
				log("asdf2");
				player->setPayable(this);
			}
			return true;
		}
	, point, nullptr);

}

void Building::upgrade() {
	isBuilding = true;
	level++;
	GameTime::addTimeDependedObject(-1, this);

	spr->setTexture(levelsImages.at(level));
	spr->getTexture()->setAliasTexParameters();
}


void Building::timeDependedAction()
{
	if (currentState > nextUpgradeDuration)
	{
		GameTime::removeTimeDependedObject(this);
	}

	currentState++;
	log("%d", currentState);
}

int Building::getLevel() {
	return level;
}

Sprite* Building::getSprite() {
	return spr;
}