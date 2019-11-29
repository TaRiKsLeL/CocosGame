#include "Enemy.h"

Enemy::Enemy(Vec2 pos) : NPC(pos, ENEMY_SPR) , HP(ENEMY_HP) {
	this->setMoveSpeed(static_cast<double>(RandomHelper::random_int<int>(ENEMY_MOVE_SPEED_MIN * ENEMY_RAND_DIVISION
		, ENEMY_MOVE_SPEED_MAX * ENEMY_RAND_DIVISION)) / ENEMY_RAND_DIVISION);
	
	spr->getPhysicsBody()->setCategoryBitmask(ENEMY_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(ENEMY_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(ENEMY_COLLIDE_BM);
}

