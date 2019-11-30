#include "Warrior.h"

Warrior::Warrior(Vec2 pos) : FriendlyNPC(pos, WARRIOR_SPR) {
	spr->setTag(SprTag::WARRIOR);

	spr->getPhysicsBody()->setCategoryBitmask(WARRIOR_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(WARRIOR_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(WARRIOR_COLLIDE_BM);

}
