#include "Warrior.h"

Warrior::Warrior(Vec2 pos) : FriendlyNPC(pos, WARRIOR_SPR), Shooter(spr) {
	spr->setTag(SprTag::WARRIOR);

	spr->getPhysicsBody()->setCategoryBitmask(WARRIOR_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(WARRIOR_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(WARRIOR_COLLIDE_BM);

}

void Warrior::timeDependedAction() {
	if (isActive && targetEnemy != nullptr) {
		shoot(targetEnemy->getPosition());
	}
}

void Warrior::removeTarget() {
	targetEnemy = nullptr;
	GameTime::removeTimeDependedObject(this);
}

void Warrior::setTarget(Node* node) {
	targetEnemy = node;
	GameTime::addTimeDependedObject(-1, this);
}
