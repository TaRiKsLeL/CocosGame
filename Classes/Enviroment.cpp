#include "Enviroment.h"
#include "SlaveTraider.h"

Enviroment* Enviroment::enviroment{ nullptr };

stack<Sprite*>*deleteTreesStack = new stack<Sprite*>();

Scene* Enviroment::getScene() {
	return scene;
}

void Enviroment::setGroundSpr(const std::string fileName) {
	groundSpr = Sprite::create(fileName);
	groundSpr->getTexture()->setAliasTexParameters();
	groundSpr->setPosition(0, GENERAL_Y + 32 / SCALE_FACTOR);
	groundSpr->setAnchorPoint(Vec2(0, 1));
	scene->addChild(groundSpr, GROUND_Z_ORDER);
}

void Enviroment::setBorders(KingdomBorders *borders)
{
	this->borders = borders;
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
	setGroundSpr(GROUND_SPR);
	setBorders(BuildingController::getInstance()->getKingdomBorders());
	EnvironmentUI::getInstance();
	Player::getInstance();
}



KingdomBorders* Enviroment::getBorders()
{
	return borders;
}

double Enviroment::getGroundWidth() {
	log("%d", groundSpr->getBoundingBox().size.width);
	return groundSpr->getBoundingBox().size.width;
}

void Enviroment::updateEnviromentData()
{
	Enviroment::getInstance()->setBorders(BuildingController::getInstance()->getKingdomBorders());
	EnvironmentUI::getInstance()->updateTrees();
	EnvironmentUI::getInstance()->createFence(Enviroment::getInstance()->getBorders());
}
