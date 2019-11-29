#include "NPC.h"

/*
=====================================================================================================
Init
=====================================================================================================
*/

NPC::NPC(Vec2 pos, std::string sprName) : isMoving(false), stop(true), moveSpeed(DEFAULT_NPC_MOVE_SPEED), direction(Direction::RIGHT){

	spr = Sprite::create(sprName);
	spr->setPosition(pos);
	spr->setAnchorPoint(Vec2(0.5, 0));
	spr->addComponent(createPhysBody());

	Director::getInstance()->getRunningScene()->addChild(spr, NPC_Z_ORDER);
}


PhysicsBody* NPC::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	return pb;
}

/*
=====================================================================================================
move and position
=====================================================================================================
*/

void NPC::resetDirection() {
	if (currentPointToMove.x > spr->getPosition().x)
		direction = Direction::RIGHT;
	else
		direction = Direction::LEFT;
}

Direction NPC::getDirection() {
	return direction;
}



void NPC::moveStart(Vec2 pos) {
	if (stop) {
		stop = false;
		currentPointToMove = pos;
		GameTime::addMoveableObject(this);
	}

}

void NPC::moveTo(Vec2 destination) {
	
	resetDirection();

	int direction;
	int delta = destination.x - spr->getPosition().x;

	if (delta >= 0)
		direction = 1;
	else
		direction = -1;

	spr->setPosition(spr->getPosition().x + direction * moveSpeed, spr->getPosition().y);

	if (spr->getPosition().x - moveSpeed / 2 <= destination.x &&
		spr->getPosition().x + moveSpeed / 2 >= destination.x)
	{
		isMoving = false;
	}
}

Vec2 NPC::getCurrentPointMoveTo() {
	return currentPointToMove;
}


void NPC::move() {
	moveTo(currentPointToMove);
}


void NPC::stopMoving() {
	if (!stop) {
		stop = true;
		GameTime::removeMoveableObject(this);
	}
}


/*
=====================================================================================================
get set
=====================================================================================================
*/

void NPC::addChild(Sprite* spr) {
	this->spr->addChild(spr);
}

void NPC::removeAllChildren() {
	spr->removeAllChildren();
}

void NPC::deleteObj() {
	spr->removeFromParentAndCleanup(true);
}

Vec2 NPC::getPosition() {
	return spr->getPosition();
}

void NPC::setMoveSpeed(float speed) {
	log("%f", speed);
	moveSpeed = speed;
}

/*
=====================================================================================================
get set
=====================================================================================================
*/

void NPC::hit(int hitPower) {

}