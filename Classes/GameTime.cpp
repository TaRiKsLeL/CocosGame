#include "GameTime.h"
#include "cocos2d.h"

int GameTime::frameCount = 0;

vector<IMoveable*> *GameTime::moveableObjects = new vector<IMoveable*>();
map<int, ITimeDepended*> *GameTime::timeDependedObjects = new map<int, ITimeDepended*>();

void GameTime::updateFrame() {
	frameCount++;
	cocos2d::log("%d", frameCount);
	cout << frameCount << endl;
}

void GameTime::addTimeDependedObject(int time, ITimeDepended* objToAdd) {
	timeDependedObjects->insert(TimeAction(time, objToAdd));
}

void GameTime::addMoveableObject(IMoveable* objToAdd) {
	moveableObjects->push_back(objToAdd);
}

void GameTime::removeTimeDependedObject(int time) {
	timeDependedObjects->erase(time);
}
void GameTime::removeMoveableObject(IMoveable* objToRemove) {

}