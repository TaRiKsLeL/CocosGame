#include "Builder.h"
#include "UI.h"
#include "AnimationCreator.h"

Builder::Builder(Vec2 pos) : FriendlyNPC(pos), goToBuilding(false), m_isBuilding(false) {
	spr->getPhysicsBody()->setCategoryBitmask(BUILDER_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(BUILDER_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(BUILDER_COLLIDE_BM);

	animWalk = AnimationCreator::getInstance()->createAnimate
	(
		BUILDER_WALK_FRAMES, 
		BUILDER_WALK_IMAGES_AMOUNT, 
		BUILDER_WALK_IMAGE_WIDTH, 
		BUILDER_WALK_IMAGE_HEIGHT, 
		BUILDER_WALK_TIME_PER_FRAME
	);

	animBuild = AnimationCreator::getInstance()->createAnimate
	(
		BUILDER_WORK_FRAMES,
		BUILDER_WORK_IMAGES_AMOUNT,
		BUILDER_WORK_IMAGE_WIDTH,
		BUILDER_WORK_IMAGE_HEIGHT,
		BUILDER_WORK_TIME_PER_FRAME
	);
	spr->runAction(animWalk);

	spr->setTag(SprTag::BUILDER);
}

void Builder::setBuild(bool isBuilding) {
	spr->removeAllChildren();
	if (isBuilding)
	{
		UI::getInstance()->addHummer(spr);
		spr->stopAllActions();
		spr->runAction(animBuild);
	}
	else {
		spr->stopAllActions();
		spr->runAction(animWalk);
	}

	
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