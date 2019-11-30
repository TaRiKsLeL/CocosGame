#include "Enemy.h"

Enemy::Enemy(Vec2 pos) : NPC(pos, ENEMY_SPR) , HP(ENEMY_HP) , attPower(ENEMY_ATTACK) {
	this->setMoveSpeed(static_cast<double>(RandomHelper::random_int<int>(ENEMY_MOVE_SPEED_MIN * ENEMY_RAND_DIVISION
		, ENEMY_MOVE_SPEED_MAX * ENEMY_RAND_DIVISION)) / ENEMY_RAND_DIVISION);
	
	spr->getPhysicsBody()->setCategoryBitmask(ENEMY_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(ENEMY_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(ENEMY_COLLIDE_BM);
}

int Enemy::getAttPower() {
	return attPower;
}

void Enemy::jmpBack() {
	spr->runAction(createJmp());
}

Action* Enemy::createJmp() {
	int jmpLen = ENEMY_JMP_LENGTH;

	if (getDirection() == Direction::RIGHT)
		jmpLen = -jmpLen;

	return JumpBy::create(ENEMY_JMP_DURATION, Vec2(jmpLen, 0), ENEMY_JMP_HEIGTH , ENEMY_JMP_QUANTITY);
}

/*
=====================================================================================================
Player hit
=====================================================================================================
*/
bool Enemy::canBeAttacked() {
	return true;
}
void Enemy::hit(int attPower) {
	
}
