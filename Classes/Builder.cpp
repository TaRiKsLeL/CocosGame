#include "Builder.h"

Builder::Builder(Vec2 pos) : FriendlyNPC(pos, BUILDER_SPR) {
	spr->getPhysicsBody()->setCategoryBitmask(BUILDER_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(BUILDER_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(BUILDER_COLLIDE_BM);
}

void Builder::setBuild(bool isBuilding) {
	this->m_isBuilding = isBuilding;
}

bool Builder::isBuilding() {
	return m_isBuilding;
}