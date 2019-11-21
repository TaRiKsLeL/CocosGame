#include "SlaveTraider.h"

SlaveTraider* SlaveTraider::slaveTraider{ nullptr };

SlaveTraider::SlaveTraider(){
	spr = Sprite::create(SLAVE_TRAIDER);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(Vec2(SLAVE_TRAIDER_START_X, SLAVE_TRAIDER_START_Y));
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);
}

SlaveTraider* SlaveTraider::getInstance() {
	if (slaveTraider)
		return slaveTraider;
	slaveTraider = new SlaveTraider();
	return slaveTraider;
}

void SlaveTraider::pay(int &money) {
	if (money >= SLAVE_PRICE) {
		money -= SLAVE_PRICE;
		createCitizen();
	}
	
}


void SlaveTraider::createCitizen() {
	CitizenController::getInstance()->create(slaveTraider->spr->getPosition());
}