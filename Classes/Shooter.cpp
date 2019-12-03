#include "Shooter.h"

Shooter::Shooter(Sprite* shooterSpr) {
	node = new Node();
	node->addComponent(createPhysicsBodyShootDiapason());
	shooterSpr->addChild(node);
	this->shooterSpr = shooterSpr;
}

PhysicsBody* Shooter::createPhysicsBodyShootDiapason() {
	
	PhysicsBody* pb = PhysicsBody::createBox(Size(WARRIOR_SHOOT_WIGTH, WARRIOR_SHOOT_HEIGTH));

	pb->setCategoryBitmask(SHOOTER_CATEGORY_BM);
	pb->setCollisionBitmask(SHOOTER_COLLIDE_BM);
	pb->setContactTestBitmask(SHOOTER_COLLIDE_BM);
	
	pb->setDynamic(false);

	return pb;
}

Node* Shooter::getTarget() {
	return targetEnemy;
}
Node* Shooter::getNode() {
	return node;
}



Sprite* Shooter::createArrow() {

	Sprite* arrowSpr = Sprite::create(ARROW_SPR);

	Vec2 arrowPos;
	arrowPos = shooterSpr->getPosition();
	arrowPos.y = shooterSpr->getPosition().y + (shooterSpr->getBoundingBox().size.height * ARROW_RELATIVE_HEIGTH);

	arrowSpr->setPosition(arrowPos);
	arrowSpr->setAnchorPoint(Vec2(0, 0));

	PhysicsBody* pb = PhysicsBody::createBox(arrowSpr->getBoundingBox().size);

	pb->setCategoryBitmask(ARROW_CATEGORY_BM);
	pb->setCollisionBitmask(ARROW_COLLIDE_BM);
	pb->setContactTestBitmask(ARROW_COLLIDE_BM);

	pb->setDynamic(false);
	arrowSpr->addComponent(pb);

	
	return arrowSpr;
}

void Shooter::shoot(Vec2 posTarget) {
	Sprite* arrow = createArrow();

	

	float rndMiss = RandomHelper::random_int<int>(-ARROW_MISS_X, ARROW_MISS_X);

	
	Director::getInstance()->getRunningScene()->addChild(arrow, ARROW_Z_ORDER);
	
	arrow->runAction(createFlyAction(posTarget.x + rndMiss, WARRIOR_SHOOT_HEIGTH));

	ArrowEraser* arrowEraser = new ArrowEraser(arrow);
	arrowEraser->setTimeDependedAction();

}

Spawn* Shooter::createFlyAction(int posX, int height) {

	Spawn* action = Spawn::createWithTwoActions(JumpTo::create(ARROW_FLY_DURATION, Vec2(posX, GENERAL_Y), height, 1), RotateBy::create(ARROW_FLY_DURATION, -90));
	return action;
}

ArrowEraser::ArrowEraser(Sprite* spr) {
	log("create Eraser");
	arrow = spr;
}


void ArrowEraser::setTimeDependedAction() {
	int eraseTime = (GameTime::getCurrentTime() + ARROW_FLY_DURATION) % DAY_DURATION;
	GameTime::addTimeDependedObject(eraseTime, this);
};


void ArrowEraser::timeDependedAction() {
	log("delete arrow");
	arrow->removeAllComponents();
	arrow->removeFromParentAndCleanup(true);
	GameTime::removeTimeDependedObject(this);
	log("remove arrow");
};




