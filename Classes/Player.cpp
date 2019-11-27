#include "Player.h"
Player* Player::player{ nullptr };


/*
=====================================================================================================
Init Player
=====================================================================================================
*/

Player::Player(const std::string fileName) {

	spr = Sprite::create(fileName);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(Vec2(PLAYER_START_X, GENERAL_Y));
	spr->getTexture()->setAliasTexParameters();
	spr->addComponent(createPhysBody());
	spr->setTag(SprTag::PLAYER);
	Enviroment::getInstance()->getScene()->addChild(spr, PLAYER_Z_ORDER);
	
	money = PLAYER_START_MONEY;
	
	initMoveListener();
	initBuyListener();
	initChoseRoleListener();

	GameTime::addMoveableObject(this);
	//
	setCamera();
	//
	objInFocus = nullptr ;

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
	player = new Player(PLAYER_SPR);
	return player;
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

	if (direction.right) {
		pos.x += PLAYER_SPEED;
	}
	if (direction.left) {
		pos.x -= PLAYER_SPEED;
	}

	spr->setPosition(pos);
}


void Player::changeMoveDirection(EventKeyboard::KeyCode keyCode, bool condition) {

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		direction.right = condition;

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		direction.left = condition;

}

void Player::initMoveListener() {

	moveListener = EventListenerKeyboard::create();

	moveListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, true);
	};

	moveListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, false);
	};

	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(moveListener, spr);
}



void Player::initBuyListener() {

	buyListener = EventListenerKeyboard::create();

	buyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {

			objInFocus->pay(this->money);
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

bool Player::checkFocusedObj(IPayable* objTocheck) {
	if (objTocheck == objInFocus)
		return true;
	return false;
}


void Player::setPayable(IPayable* objInFocus) {

	if (this->objInFocus == nullptr) 
	{
		this->objInFocus = objInFocus;
		log("create listener");
		buyListener->setEnabled(true);
	}
}

bool Player::focused() {
	if (objInFocus == nullptr)
		return false;
	else
		return true;
}
