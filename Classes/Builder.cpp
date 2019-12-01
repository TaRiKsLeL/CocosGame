#include "Builder.h"
#include "UI.h"

Builder::Builder(Vec2 pos) : FriendlyNPC(pos, BUILDER_SPR), goToBuilding(false), m_isBuilding(false) {
	spr->getPhysicsBody()->setCategoryBitmask(BUILDER_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(BUILDER_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(BUILDER_COLLIDE_BM);

	spr->setTag(SprTag::BUILDER);
}

void Builder::setBuild(bool isBuilding) {
	spr->removeAllChildren();
	if (isBuilding)
		UI::getInstance()->addHummer(spr);
	
	this->m_isBuilding = isBuilding;
}

bool Builder::isBuilding() {
	return m_isBuilding;
}

bool Builder::isMovingToBuilding() {
	return goToBuilding;
}

void Builder::setMovingToBuild(bool isMoving) {
	spr->removeAllChildren();
	if (isMoving)
		UI::getInstance()->addMark(spr);
	
	goToBuilding = isMoving;
}