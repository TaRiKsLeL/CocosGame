#include "Warrior.h"

Warrior::Warrior(Vec2 pos) : FriendlyNPC(pos, WARRIOR_SPR), Shooter(spr), inTower(false) {
	spr->setTag(SprTag::WARRIOR);

	spr->getPhysicsBody()->setCategoryBitmask(WARRIOR_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(WARRIOR_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(WARRIOR_COLLIDE_BM);

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

