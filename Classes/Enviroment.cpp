#include "Enviroment.h"

Enviroment* Enviroment::enviroment{ nullptr };

Scene* Enviroment::getScene() {
	return scene;
}

void Enviroment::setGroundSpr(const std::string fileName) {
	groundSpr = Sprite::create(fileName);
	groundSpr->getTexture()->setAliasTexParameters();
	groundSpr->setAnchorPoint(Vec2(0, 0));
	scene->addChild(groundSpr, GROUND_Z_ORDER);
}


void Enviroment::setScene(Scene* scene) {
	this->scene = scene;
	addComponents();
}

Enviroment* Enviroment::getInstance() {
	if (enviroment)
		return enviroment;
	enviroment = new Enviroment();
	return enviroment;
}

void Enviroment::addComponents() {
	setGroundSpr(GROUND);
	BuildingController::getInstance();
	Player::getInstance();
}

double Enviroment::getGroundWidth() {
	return groundSpr->getBoundingBox().size.width;
}