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
	pb->setContactTestBitmask(true);
	pb->setDynamic(false);
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

