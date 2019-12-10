#include "Worker.h"
#include "AnimationCreator.h"

Worker::Worker(Vec2 pos) : FriendlyNPC(pos) {
	spr->setTag(SprTag::WORKER);

	spr->getPhysicsBody()->setCategoryBitmask(WORKER_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(WORKER_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(WORKER_COLLIDE_BM);

	animWalk = AnimationCreator::getInstance()->createAnimate
	(
		WORKER_WALK_FRAMES,
		WORKER_WALK_IMAGES_AMOUNT,
		WORKER_WALK_IMAGE_WIDTH,
		WORKER_WALK_IMAGE_HEIGHT,
		WORKER_WALK_TIME_PER_FRAME
	);
	spr->runAction(animWalk);
}


Sprite* Worker::getSprite()
{
	return spr;
}



