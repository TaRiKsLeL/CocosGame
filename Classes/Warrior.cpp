#include "Warrior.h"
#include "AnimationCreator.h"

Warrior::Warrior(Vec2 pos) : FriendlyNPC(pos), Shooter(spr), inTower(false) {
	spr->setTag(SprTag::WARRIOR);

	spr->getPhysicsBody()->setCategoryBitmask(WARRIOR_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(WARRIOR_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(WARRIOR_COLLIDE_BM);

	animWalk = AnimationCreator::getInstance()->createAnimate
	(
		WARRIOR_WALK_FRAMES,
		WARRIOR_WALK_IMAGES_AMOUNT,
		WARRIOR_WALK_IMAGE_WIDTH,
		WARRIOR_WALK_IMAGE_HEIGHT,
		WARRIOR_WALK_TIME_PER_FRAME
	);
	spr->runAction(animWalk);

}

void Warrior::timeDependedAction() {
	if (isActive && targetEnemy!=nullptr) {
		shoot(targetEnemy->getPosition());
	}
}

void Warrior::removeTarget() {
	targetEnemy = nullptr;
	GameTime::removeTimeDependedObject(this);
}

void Warrior::setTarget(Node* node) {
	if (targetEnemy == nullptr) {
		targetEnemy = node;
		GameTime::addTimeDependedObject(-1, this);
	}
}

void Warrior::setFixedPosition(Vec2 pos) {
	inTower = true;
	spr->removeAllComponents();
	spr->setZOrder(WARRIOR_ON_TOWER_Z_ORDER);
	stopMoving();
	spr->setPosition(pos);
}

bool Warrior::isOnTower() {
	return inTower;
}

