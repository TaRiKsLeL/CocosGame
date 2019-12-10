#include "NPC.h"
#include "Player.h"

/*
=====================================================================================================
Init
=====================================================================================================
*/

NPC::NPC(Vec2 pos) : m_isMoving(false), stop(true), goingToRemove(false), moveSpeed(DEFAULT_NPC_MOVE_SPEED), direction(Direction::RIGHT){

	spr = Sprite::create(NPS_BASE_SPR);
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

	setSprDirection(direction);
}

Direction NPC::getDirection() {
	return direction;
}



void NPC::moveStart(Vec2 pos) {
	if (stop) {
		stop = false;
		m_isMoving = true;
		currentPointToMove = pos;
		GameTime::addMoveableObject(this);
	}

}

void NPC::moveTo(Vec2 destination)
{
	int direction;
	
	if (spr == nullptr )
		return;


	
		resetDirection();


		int delta = destination.x - spr->getPosition().x;

		if (delta >= 0)
			direction = 1;
		else
			direction = -1;

		spr->setPosition(spr->getPosition().x + direction * moveSpeed, spr->getPosition().y);

	if (spr->getPosition().x - moveSpeed / 2 <= destination.x &&
		spr->getPosition().x + moveSpeed / 2 >= destination.x)
	{
		m_isMoving = false;
	}
}

bool NPC::isGoingToRemove() {
	return goingToRemove;
}


Vec2 NPC::getCurrentPointMoveTo() {
	return currentPointToMove;
}


void NPC::move() {
	if(m_isMoving)
		moveTo(currentPointToMove);
}


void NPC::stopMoving() {
	if (!stop) {
		m_isMoving = false;
		stop = true;
		GameTime::removeMoveableObject(this, false);
	}
}

void NPC::setSprDirection(Direction dir) {
	if (dir == Direction::RIGHT) {
		direction = dir;
		spr->setFlipX(-1);
	}
	else {
		direction = dir;
		spr->setFlipX(0);
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
	if (Payable* p = dynamic_cast<Payable*>(this)) {
		if (Player::getInstance()->checkFocusedObj(p)) 
			Player::getInstance()->setPayable(nullptr);
		
	}
	goingToRemove = true;
	GameTime::removeMoveableObject(this, true);
	spr->removeAllComponents();
	spr->removeFromParentAndCleanup(true);
	spr = nullptr;
}

Vec2 NPC::getPosition() {
	return spr->getPosition();
}

Rect NPC::getBoundingBox() {
	return spr->getBoundingBox();
}

void NPC::setMoveSpeed(float speed) {
	moveSpeed = speed;
}

bool NPC::isMoving() {
	return m_isMoving;
}