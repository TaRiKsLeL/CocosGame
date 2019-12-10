#include "Player.h"
#include "AnimationCreator.h"
#include "EnvironmentUI.h"

Player* Player::player{ nullptr };


/*
=====================================================================================================
Init Player
=====================================================================================================
*/

Player::Player(const std::string fileName) : money(PLAYER_START_MONEY) , objInFocus(nullptr), m_HP(PLAYER_HP) {

	spr = Sprite::create(fileName);
	spr->setAnchorPoint(Vec2(0.5, 0));
	spr->setPosition(Vec2(PLAYER_START_X, GENERAL_Y));
	spr->getTexture()->setAliasTexParameters();
	spr->addComponent(createPhysBody());
	spr->setTag(SprTag::PLAYER);

	idle = AnimationCreator::getInstance()->createAnimate
	(
		PLAYER_IDLE_FRAMES,
		PLAYER_IDLE_IMAGES_AMOUNT,
		PLAYER_IDLE_IMAGE_WIDTH,
		PLAYER_IDLE_IMAGE_HEIGHT,
		PLAYER_IDLE_TIME_PER_FRAME
	);

	run = AnimationCreator::getInstance()->createAnimate
	(
		PLAYER_RUN_FRAMES,
		PLAYER_RUN_IMAGES_AMOUNT,
		PLAYER_RUN_IMAGE_WIDTH,
		PLAYER_RUN_IMAGE_HEIGHT,
		PLAYER_RUN_TIME_PER_FRAME
	);

	spr->runAction(idle);

	spr->setTextureRect(Rect(0, 0, spr->getContentSize().width, spr->getContentSize().height));
	Enviroment::getInstance()->getScene()->addChild(spr, PLAYER_Z_ORDER);
	
	money = PLAYER_START_MONEY;
	m_HP = PLAYER_MAX_HEALTH;

	initMoveListener();
	initBuyListener();
	initChoseRoleListener();

	GameTime::addMoveableObject(this);
	//
	setCamera();
	//
	player = this;
}

void Player::setCamera()
{
	Rect camRect = Rect::ZERO;
	auto follow = Follow::createWithOffset(spr, 0, CAMERA_OFFSET_Y, camRect);
	Enviroment::getInstance()->getScene()->runAction(follow);
}



Player* Player::getInstance() {
	if (player)
		return player;
	player = new Player(PLAYER_RUN_IMAGE);
	return player;
}

Sprite* Player::getSprite()
{
	return spr;
}

void Player::moveBackground(int fatherSpeed)
{
	EnvironmentUI::getInstance()->getBaseNode()->setPosition(spr->getPosition());
}



PhysicsBody* Player::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	pb->setContactTestBitmask(PLAYER_COLLIDE_BM);
	pb->setCategoryBitmask(PLAYER_CATEGORY_BM);
	pb->setCollisionBitmask(PLAYER_COLLIDE_BM);
	return pb;
}



/*
=====================================================================================================
Player movement 
=====================================================================================================
*/



void Player::move() {

	if (isDisabledChoseRoleListener) {
		choseRoleListener->setEnabled(false);
		isDisabledChoseRoleListener = false;
	}

	Vec2 pos = spr->getPosition();
	
		if (direction.right && pos.x < Enviroment::getInstance()->getGroundWidth()) {
			pos.x += PLAYER_SPEED;
		}
		if (direction.left && pos.x > 0) {
			pos.x -= PLAYER_SPEED;
		}
	spr->setPosition(pos);
	
}


void Player::changeMoveDirection(EventKeyboard::KeyCode keyCode, bool condition) {

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		spr->setFlipX(-1);
		direction.right = condition;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		spr->setFlipX(0);
		direction.left = condition;
	}
}

void Player::initMoveListener() {

	moveListener = EventListenerKeyboard::create();

	moveListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, true);
		spr->stopAllActions();
		spr->runAction(run);
	};

	moveListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, false);
		spr->stopAllActions();
		spr->runAction(idle);
	};

	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(moveListener, spr);
}



void Player::initBuyListener() {

	buyListener = EventListenerKeyboard::create();

	buyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {

			objInFocus->pay(this->money);
			UI::getInstance()->getCoinsLabel()->setString(to_string(this->money));
		}
	};
	
	buyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {};

	buyListener->setEnabled(false);

	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(buyListener, spr);
}



void Player::initChoseRoleListener() {

	choseRoleListener = EventListenerKeyboard::create();

	choseRoleListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			CitizenController::getInstance()->setNewRole(SprTag::WARRIOR, objInFocus);
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			CitizenController::getInstance()->setNewRole(SprTag::BUILDER, objInFocus);
			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			CitizenController::getInstance()->setNewRole(SprTag::WORKER, objInFocus);
			break;
		default:
			break;
		}

		
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			objInFocus = nullptr;
			isDisabledChoseRoleListener = true;
		}
	};

	buyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {};

	choseRoleListener->setEnabled(false);

	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(choseRoleListener, spr);
}

void Player::removeAllListeners() {
	GameTime::removeMoveableObject(this, false);
	static_cast<GameScene*>(Director::getInstance()->getRunningScene())->removeKeyEventListener(buyListener);
	static_cast<GameScene*>(Director::getInstance()->getRunningScene())->removeKeyEventListener(choseRoleListener);
	static_cast<GameScene*>(Director::getInstance()->getRunningScene())->removeKeyEventListener(moveListener);
}


/*
=====================================================================================================
Player key act
=====================================================================================================
*/


void Player::enableChoseRoleListener() {
	choseRoleListener->setEnabled(true);
}

void Player::disableBuyListener() {
	buyListener->setEnabled(false);
}


void Player::disableFocusBuyListener() {
	if (objInFocus != nullptr)
	{
		buyListener->setEnabled(false);

		objInFocus->onChangeFocus();
		objInFocus = nullptr;
	}
}

/*
=====================================================================================================
Player Pay
=====================================================================================================
*/



void Player::addMoney(int moneyToAdd) {
	this->money += moneyToAdd;
}
int& Player::getMoney() {
	return this->money;
}

void Player::addHP(int val)
{ 
	m_HP += val;
}

int& Player::getHP()
{
	return m_HP;
}

void Player::addChild(Node* child)
{
	spr->addChild(child);
}

void Player::removeAllChildren()
{
	spr->removeAllChildren();
}

bool Player::checkFocusedObj(Payable* objTocheck) {
	if (objTocheck == objInFocus)
		return true;
	return false;
}


void Player::setPayable(Payable* objInFocus) {

	if (this->objInFocus == nullptr) 
	{
		this->objInFocus = objInFocus;
		buyListener->setEnabled(true);
	}
}

bool Player::focused() {
	if (objInFocus == nullptr)
		return false;
	else
		return true;
}

/*
=====================================================================================================
Player hit
=====================================================================================================
*/

void Player::hit(int attPower) {
	m_HP -= attPower;
	UI::getInstance()->updateHeartLogo(m_HP);
	if (m_HP <= 0) {
		UI::getInstance()->setGameOverSprite(GAME_OVER_BACK_SPR);
		EnemyController::getInstance()->allStopMove();
	}
}

bool Player::canBeAttacked() {
	return true;
}
