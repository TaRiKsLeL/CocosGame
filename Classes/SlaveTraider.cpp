#include "SlaveTraider.h"

SlaveTraider* SlaveTraider::slaveTraider{ nullptr };

SlaveTraider::SlaveTraider(){
	spr = Sprite::create(SLAVE_TRAIDER_SPR);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(Vec2(SLAVE_TRAIDER_START_X, GENERAL_Y));
	spr->setTag(SprTag::SLAVE_TRAIDER);

	spr->addComponent(createPhysBody());

	setQueryRect();
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

void SlaveTraider::pay(int &money) {
	if (money >= SLAVE_PRICE) {
		money -= SLAVE_PRICE;
		createCitizen();
	}
	
}


void SlaveTraider::createCitizen() {
	CitizenController::getInstance()->create(slaveTraider->spr->getPosition());
}

void SlaveTraider::setQueryRect() {

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
	,point , nullptr);

	
}