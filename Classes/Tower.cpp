#include "Tower.h"

Tower::Tower(vector<std::string> images):Building(images) {

}

Tower::Tower(bool dir, vector<std::string> images) : Building(images) {
	if (dir) {
		direction.right = dir;
		spr->setFlipX(-1);
	}
	else {
		direction.left = dir;
	}
}