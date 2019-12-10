#include "EnvironmentUI.h"

EnvironmentUI* EnvironmentUI::environmentUI{ nullptr };

EnvironmentUI::EnvironmentUI() 
{
	baseNode = Node::create();
	baseNode->setPosition(Vec2(Player::getInstance()->getSprite()->getPositionX(), Player::getInstance()->getSprite()->getPositionY()));
	Enviroment::getInstance()->getScene()->addChild(baseNode, BACKGROUND_Z_ORDER);

	setBackground();
	generateTrees();
}

EnvironmentUI* EnvironmentUI::getInstance()
{
	if (environmentUI)
		return environmentUI;
	environmentUI = new EnvironmentUI();
	return environmentUI;
}

void EnvironmentUI::generateTrees()
{

	for (int i = 0; i < TREES_AMOUNT; i++) {
		int randTreeIndex = 0 + rand() % TREES.size();
		int color = 0 + rand() % 4;

		int randXPosition;
		do {
			randXPosition = 0 + rand() % static_cast<int>(Enviroment::getInstance()->getGroundWidth());

		} while (pointIntersectsTree(randXPosition) || Enviroment::getInstance()->getBorders()->isInKingdom(randXPosition));

		trees.push_back(Sprite::create(TREES.at(randTreeIndex)));
		trees.at(i)->setAnchorPoint(Vec2(0.5, 0));
		trees.at(i)->setPosition(randXPosition, GENERAL_Y);
		trees.at(i)->setScale(random(1.8f,2.2f));
		if (color == 0) {
			trees.at(i)->setColor(Color3B(222, 198, 172));
		}
		else if (color == 1) {
			trees.at(i)->setColor(Color3B(199, 119, 119));
		}
		if (0 + rand() % 2) {
			trees.at(i)->setFlipX(true);
		}
		trees.at(i)->getTexture()->setAliasTexParameters();
		Enviroment::getInstance()->getScene()->addChild(trees.at(i), TREE_Z_ORDER);

	}

}

void EnvironmentUI::updateTrees()
{
	static stack<Sprite*>* deleteTreesStack = new stack<Sprite*>();
	for each (Sprite * sp in trees)
	{
		if (Enviroment::getInstance()->getBorders()->isInKingdom(sp->getPositionX()))
		{
			deleteTreesStack->push(sp);
			Enviroment::getInstance()->getScene()->removeChild(sp);
		}
	}

	while (deleteTreesStack->size() > 0) {
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

void EnvironmentUI::createFence(KingdomBorders* borders)
{

	static vector<Sprite*> fence;

	for each (Sprite* sprite in fence)
	{
		Enviroment::getInstance()->getScene()->removeChild(sprite);
	}


	float tempX = borders->leftX;
	while (tempX < borders->rightX) {
		auto spr = Sprite::create(FENCE_SPR);
		spr->setAnchorPoint(Vec2(0, 0));
		spr->setPosition(tempX, GENERAL_Y);
		spr->getTexture()->setAliasTexParameters();
		fence.push_back(spr);
		Enviroment::getInstance()->getScene()->addChild(spr, FENCE_Z_ORDER);
		tempX += spr->getContentSize().width;
	}

}

bool EnvironmentUI::pointIntersectsTree(float xPos)
{
	for each (Sprite * tree in trees)
	{
		if (tree->getBoundingBox().containsPoint(Vec2(xPos, tree->getPositionY()))) {
			return true;
		}
	}

	return false;
}

Node* EnvironmentUI::getBaseNode()
{
	return baseNode;
}

map<Sprite*, float>* EnvironmentUI::getParallaxMap()
{
	return &parallaxMap;
}

MoveDirection EnvironmentUI::getWindDir()
{
	return windDirection;
}

Action* EnvironmentUI::createMoveByActionCloud(int speed,int dist)
{
	auto moving = MoveBy::create(speed, Vec2(dist,0));
	moving->setTag(1);
	moving->retain();

	return moving;
}

void EnvironmentUI::updateBackground()
{
	/*skySpr->setPosition(Vec2(Player::getInstance()->getSprite()->getPosition().x, Player::getInstance()->getSprite()->getPosition().y+ CAMERA_OFFSET_Y-100));

	Point playerPosition = Player::getInstance()->getSprite()->getPosition();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (cloudsSpr->getPositionX() < playerPosition.x) {
		cloudsSpr->setPosition(Vec2(cloudsSpr->getPositionX() + CLOUDS_SPEED, cloudsSpr->getPositionY()));
	}
	if (cloudsSpr->getPositionX() > playerPosition.x) {
		cloudsSpr->setPosition(Vec2(cloudsSpr->getPositionX() - CLOUDS_SPEED, cloudsSpr->getPositionY()));
	}

	Point rightBound = Vec2(playerPosition.x + DISTANCE_TO_ENDING_OF_SCREEN, 0);

	Point leftBound = Vec2(playerPosition.x - DISTANCE_TO_ENDING_OF_SCREEN, 0);


	if (cloudsSpr->getPositionX() > rightBound.x) {
		cloudsSpr->setPosition(Vec2(cloudsSpr->getPositionX() - DISTANCE_TO_ENDING_OF_SCREEN * 2, cloudsSpr->getPositionY()));
	}

	if (cloudsSpr->getPositionX() < leftBound.x) {
		cloudsSpr->setPosition(Vec2(cloudsSpr->getPositionX() + DISTANCE_TO_ENDING_OF_SCREEN * 2, cloudsSpr->getPositionY()));
	}*/
}

void EnvironmentUI::setBackground()
{
	skySpr = Sprite::create(SKY_SPR);
	skySpr->getTexture()->setAliasTexParameters();
	skySpr->setPositionY(-CAMERA_OFFSET_Y);
	baseNode->addChild(skySpr,-7);

	if (random(0, 2) == 0) {
		windDirection.right = false;
		windDirection.left = true;
	}
	else {
		windDirection.left = false;
		windDirection.right = true;
	}

	for (int i = 0; i < APPROX_CLOUDS_AMOUNT; i++) {

		Sprite* sp = Sprite::create(CLOUDS.at(random(0, static_cast<int>(CLOUDS.size())-1)));
		sp->getTexture()->setAliasTexParameters();
		sp->setPosition(Vec2(random(-Enviroment::getInstance()->getGroundWidth()/2, Enviroment::getInstance()->getGroundWidth()/2), random(0, 500)));
		sp->setScale(random(CLOUD_SIZE_RAND_FACTOR, 1 + CLOUD_SIZE_RAND_FACTOR));
		sp->setTag(5);
		if (windDirection.left) {
			sp->runAction(createMoveByActionCloud(random(200, 300),-Enviroment::getInstance()->getGroundWidth() / 4));
		}
		else {
			sp->runAction(createMoveByActionCloud(random(200,300),Enviroment::getInstance()->getGroundWidth() / 4));
		}
		baseNode->addChild(sp, -5);

		parallaxMap.insert(pair<Sprite*, float>(sp, random(0.3f,0.5f)));

	}

	setSeamlessSprite(LAYER_FIRST_SPR,LAYER_FIRST_SPEED, BACK_LAYER_FIRST_OFFSET, BACK_LAYER_FIRST_Z_ORDER);
	setSeamlessSprite(LAYER_SECOND_SPR,LAYER_SECOND_SPEED, BACK_LAYER_SECOND_OFFSET, BACK_LAYER_SECOND_Z_ORDER);
	setSeamlessSprite(LAYER_TREES_BACK_SPR,LAYER_TREES_BACK_SPEED, BACK_TREES_BACK_OFFSET, BACK_TREES_Z_ORDER);
	setSeamlessSprite(LAYER_TREES_SPR,LAYER_TREES_SPEED, BACK_TREES_OFFSET, BACK_TREES_BACK_Z_ORDER);

}

void EnvironmentUI::setSeamlessSprite(string path, float speed, int yOffset, int zOrder)
{
	float tempX = -DISTANCE_TO_ENDING_OF_SCREEN;
	while (tempX < Enviroment::getInstance()->getGroundWidth() + DISTANCE_TO_ENDING_OF_SCREEN) {
		auto layer = Sprite::create(path);
		layer->setPosition(tempX, yOffset);
		layer->setAnchorPoint(Vec2(0.5, 0));
		layer->getTexture()->setAliasTexParameters();
		baseNode->addChild(layer, zOrder);
		tempX += layer->getContentSize().width;
		parallaxMap.insert(pair<Sprite*, float>(layer, speed));
	}
}

