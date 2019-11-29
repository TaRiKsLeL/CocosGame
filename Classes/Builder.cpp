#include "Builder.h"

Builder::Builder(Vec2 pos) : FriendlyNPC(pos, BUILDER_SPR) {
	m_isBuilding = false;
	spr->getPhysicsBody()->setCategoryBitmask(BUILDER_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(BUILDER_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(BUILDER_COLLIDE_BM);

	spr->setTag(SprTag::BUILDER);
}

void Builder::setBuild(bool isBuilding) {
	this->m_isBuilding = isBuilding;
}

bool Builder::isBuilding() {
	return m_isBuilding;
}