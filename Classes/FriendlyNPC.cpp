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


	moveRandStart();
}

/*
=====================================================================================================
move and position
=====================================================================================================
*/


void FriendlyNPC::moveRandStart() {
	if (stop) {
		m_isMoving = false;
		stop = false;
		isMovingRand = true;
		GameTime::addMoveableObject(this);
	}

}



Vec2 FriendlyNPC::getCurrentPointMoveTo() {
	return currentPointToMove;
}


void FriendlyNPC::move() {

	if (!m_isMoving && isMovingRand) {
		currentPointToMove.y = GENERAL_Y;
		currentPointToMove.x = RandomHelper::random_int<int>(static_cast<int>(Enviroment::getInstance()->getBorders()->leftX),
																static_cast<int>(Enviroment::getInstance()->getBorders()->rightX));
		m_isMoving = true;
	}
	else if(!m_isMoving) {
		stopMoving();
	}
	if(isActive & m_isMoving)
		moveTo(currentPointToMove);

}

void FriendlyNPC::stopMoving() {
	if (!stop) {
		stop = true;
		isMovingRand = false;
		m_isMoving = false;
		GameTime::removeMoveableObject(this, false);
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

