#include "GameTime.h"


int GameTime::frameCount{ 0 };

vector<IMoveable*> *GameTime::moveableObjects = new vector<IMoveable*>();

map<ITimeDepended*,int> *GameTime::timeDependedObjects = new map<ITimeDepended*,int>();

void GameTime::updateFrame() {
	frameCount++;

	for (IMoveable* tmpObj : *moveableObjects) {
		tmpObj->move();
	}

	if (frameCount >= DELTA_TIME) {
		frameCount = 0;
		for each (TimeAction tmpPair in *timeDependedObjects)
		{
			tmpPair.first->timeDependedAction();
		}
	}
}

void GameTime::addTimeDependedObject(int time, ITimeDepended* objToAdd) {
	timeDependedObjects->insert(TimeAction(objToAdd,time));
}

void GameTime::addMoveableObject(IMoveable* objToAdd) {
	moveableObjects->push_back(objToAdd);
}

void GameTime::removeTimeDependedObject(ITimeDepended* objToErase) {
	timeDependedObjects->erase(objToErase);
}
void GameTime::removeMoveableObject(IMoveable* objToRemove) {

}