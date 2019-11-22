#include "Wall.h"

Wall::Wall(vector<std::string> images):Building(images) {

}

Wall::Wall(bool dir,vector<std::string> images) : Building(images) {
	if (dir) {
		direction.right = dir;
		spr->setFlipX(-1);
	}
	else {
		direction.left = dir;
	}
}

void Wall::repair() {
	level = lastLevel;
}