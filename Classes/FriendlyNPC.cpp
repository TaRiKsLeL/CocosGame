#include "FriendlyNPC.h"
#include"Enviroment.h"

/*
=====================================================================================================
Init
=====================================================================================================
*/

FriendlyNPC::FriendlyNPC(Vec2 pos, std::string sprName) : NPC(pos, sprName) {
	
	setActive();
	setMoveSpeed(FRIENDLY_NPC_MOVE_SPEED);
	isMovingRand = true;

	spr->getPhysicsBody()->setCategoryBitmask(NPC_CATEGORY_BM);
	spr->getPhysicsBody()->setCollisionBitmask(NPC_COLLIDE_BM);
	spr->getPhysicsBody()->setContactTestBitmask(NPC_COLLIDE_BM);

	moveRandStart();
}

/*
=====================================================================================================
move and position
=====================================================================================================
*/


void FriendlyNPC::moveRandStart() {
	if (stop) {
		
		stop = false;
		isMovingRand = true;
		GameTime::addMoveableObject(this);
	}

}

void FriendlyNPC::moveStart(Vec2 pos) {
	if (stop) {
		stop = false;
		currentPointToMove = pos;
		GameTime::addMoveableObject(this);
	}

}



Vec2 FriendlyNPC::getCurrentPointMoveTo() {
	return currentPointToMove;
}


void FriendlyNPC::move() {

	if (!isMoving && isMovingRand) {
		currentPointToMove.y = GENERAL_Y;
		currentPointToMove.x = RandomHelper::random_int<int>(static_cast<int>(Enviroment::getInstance()->getBorders()->leftX),
																static_cast<int>(Enviroment::getInstance()->getBorders()->rightX));
		isMoving = true;
	}
	if(isActive)
		moveTo(currentPointToMove);

}

void FriendlyNPC::stopMoving() {
	if (!stop) {
		stop = true;
		isMovingRand = false;
		GameTime::removeMoveableObject(this);
	}
}

/*
=====================================================================================================
active/unactive
=====================================================================================================
*/


void FriendlyNPC::setUnactive() {
	isActive = false;
}

void FriendlyNPC::setActive() {
	isActive = true;
}


/*
=====================================================================================================
FriendlyNPC attacked
=====================================================================================================
*/

bool FriendlyNPC::canBeAttacked() {
	if(isActive)
		return true;
	log("dead inside");
	return false;
}

void FriendlyNPC::hit(int) {
	isActive = false;
}

void FriendlyNPC::pay(int& money) {
	if (!isActive && money >= NPC_RERIVE) {
		money -= NPC_RERIVE;
		setActive();
	}
}

