#include "SlaveTraider.h"


/*
=====================================================================================================
init
=====================================================================================================
*/


SlaveTraider* SlaveTraider::slaveTraider{ nullptr };

SlaveTraider::SlaveTraider(){
	spr = Sprite::create(SLAVE_TRAIDER_SPR);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(Vec2(SLAVE_TRAIDER_START_X, GENERAL_Y));
	spr->setTag(SprTag::SLAVE_TRAIDER);
	spr->getTexture()->setAliasTexParameters();
	spr->addComponent(createPhysBody());
	
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);
}

SlaveTraider* SlaveTraider::getInstance() {
	if (slaveTraider)
		return slaveTraider;
	slaveTraider = new SlaveTraider();
	return slaveTraider;
}

PhysicsBody* SlaveTraider::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	pb->setCategoryBitmask(SLAVE_TRAIDER_CATEGORY_BM);
	pb->setCollisionBitmask(SLAVE_TRAIDER_COLLIDE_BM);
	pb->setContactTestBitmask(SLAVE_TRAIDER_COLLIDE_BM);
	return pb;
}


/*
=====================================================================================================
createCitizen and pay
=====================================================================================================
*/


void SlaveTraider::pay(int &money) {
	if (money >= SLAVE_PRICE) {
		money -= SLAVE_PRICE;
		createCitizen();
	}
}


void SlaveTraider::createCitizen() 
{
	CitizenController::getInstance()->create(slaveTraider->spr->getPosition());
}

void SlaveTraider::setSelector()
{
	setSelectorSpr(spr);
}
