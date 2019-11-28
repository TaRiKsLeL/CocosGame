#include "Enviroment.h"

Enviroment* Enviroment::enviroment{ nullptr };

stack<Sprite*>*deleteTreesStack = new stack<Sprite*>();

Scene* Enviroment::getScene() {
	return scene;
}

void Enviroment::setGroundSpr(const std::string fileName) {
	groundSpr = Sprite::create(fileName);
	groundSpr->getTexture()->setAliasTexParameters();
	groundSpr->setAnchorPoint(Vec2(0, 0));
	scene->addChild(groundSpr, GROUND_Z_ORDER);
}

void Enviroment::setBorders(KingdomBorders *borders)
{
	this->borders = borders;
}

void Enviroment::generateTrees()
{
	
	for (int i = 0; i < TREES_AMOUNT; i++) {
		int randTreeIndex = 0 + rand() % TREES.size();
		double f = (double)rand() / RAND_MAX;
		double scaleFactor = 1.7 + f * (2.4 - 1.7);
		int color = 0 + rand() % 4;

		int randXPosition;
		do {
			randXPosition = 0 + rand() % static_cast<int>(Enviroment::getInstance()->getGroundWidth());
			
		} while (pointIntersectsTree(randXPosition) || borders->isInKingdom(randXPosition));

		trees.push_back(Sprite::create(TREES.at(randTreeIndex)));
		trees.at(i)->setAnchorPoint(Vec2(0.5, 0));
		trees.at(i)->setPosition(randXPosition, GENERAL_Y);
		trees.at(i)->setScale(scaleFactor);
		if (color == 0) {
			trees.at(i)->setColor(Color3B(222, 198, 172));
		}
		else if(color==1) {
			trees.at(i)->setColor(Color3B(199, 119, 119));
		}
		if (0 + rand() % 2) {
			trees.at(i)->setFlipX(true);
		}
		trees.at(i)->getTexture()->setAliasTexParameters();
		this->getScene()->addChild(trees.at(i),TREE_Z_ORDER);

	}

}

void Enviroment::updateTrees()
{
	static stack<Sprite*>* deleteTreesStack = new stack<Sprite*>();
	for each (Sprite* sp in trees)
	{
		if (borders->isInKingdom(sp->getPositionX()))
		{
			deleteTreesStack->push(sp);
			getScene()->removeChild(sp);
		}
	}

	while (deleteTreesStack->size()> 0) {
		for (int i = 0; i < trees.size(); i++) {
			if (trees.at(i) == deleteTreesStack->top()) {
				trees.erase(trees.begin() + i);

				deleteTreesStack->pop();
				if (deleteTreesStack->size() == 0)
					break;
			}
		}
	}


	
}

void Enviroment::createFence()
{
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

bool Enviroment::pointIntersectsTree(float xPos)
{
	for each (Sprite* tree in trees)
	{
		if (tree->getBoundingBox().containsPoint(Vec2(xPos, tree->getPositionY()))) {
			return true;
		}
	}

	return false;
}

void Enviroment::addComponents() {
	setGroundSpr(GROUND_SPR);
	BuildingController::getInstance()->getWalls().at(0)->upgrade();
	BuildingController::getInstance()->getWalls().at(1)->upgrade();
	setBorders(BuildingController::getInstance()->getKingdomBorders());
	generateTrees();
	Player::getInstance();
}





KingdomBorders* Enviroment::getBorders()
{
	return borders;
}

double Enviroment::getGroundWidth() {
	return groundSpr->getBoundingBox().size.width;
}