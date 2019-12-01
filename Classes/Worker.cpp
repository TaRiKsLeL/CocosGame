#include "Worker.h"

Worker::Worker(Vec2 pos) : FriendlyNPC(pos, WORKER_SPR) {
	spr->setTag(SprTag::WORKER);

	spr->getPhysicsBody()->setCategoryBitmask(WORKER_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(WORKER_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(WORKER_COLLIDE_BM);

	isMovingToMine = false;
}

void Worker::setMovingToMine(bool kek)
{
	isMovingToMine = kek;
}

bool Worker::movingToMine()
{
	return isMovingToMine;
}
