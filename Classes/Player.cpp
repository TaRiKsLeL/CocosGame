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
	spr->setPosition(Vec2(PLAYER_START_X, GENERAL_Y_ANCHOR));
	spr->getTexture()->setAliasTexParameters();
	spr->addComponent(createPhysBody());
	spr->setTag(SprTag::PLAYER);

	Follow* follow = Follow::create(spr, Rect::ZERO);
	Enviroment::getInstance()->getScene()->addChild(spr, PLAYER_Z_ORDER);
	Enviroment::getInstance()->getScene()->runAction(follow);

	money = PLAYER_START_MONEY;
	
	moveListener = EventListenerKeyboard::create();
	setKeyListener(&Player::onMoveKeyPressed, moveListener);
	GameTime::addMoveableObject(this);

	objInFocus = nullptr ;

	player = this;
}



Player* Player::getInstance() {
	if (player)
		return player;
	player = new Player(PLAYER_SPR);
	return player;
}



PhysicsBody* Player::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setContactTestBitmask(true);
	pb->setDynamic(false);
	return pb;
}



/*
=====================================================================================================
Player movement
=====================================================================================================
*/



void Player::move() {
	Vec2 pos = spr->getPosition();

	if (direction.right) {
		pos.x += PLAYER_SPEED;
	}
	if (direction.left) {
		pos.x -= PLAYER_SPEED;
	}

	spr->setPosition(pos);
}



void Player::setKeyListener(void (Player::*moveFuncPointer)(), EventListenerKeyboard* listener) {
	(*this.*moveFuncPointer)();
	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(listener, spr);
}



void Player::onMoveKeyPressed(){

	moveListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, true);
	};

	moveListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, false);
	};
}



void Player::changeMoveDirection(EventKeyboard::KeyCode keyCode, bool condition) {
	
	if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		direction.right = condition;

	if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		direction.left = condition;

}



void Player::onKeyPressedAct() {
	actListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		setActKeys(keyCode);
	};
	actListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {};
}

void Player::setActKeys(EventKeyboard::KeyCode keyCode){
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		objInFocus->pay(this->money);
	}
}


void Player::removeActListener() {
	log("remove listener");
	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->removeKeyEventListener(actListener);
	objInFocus = nullptr;
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



void Player::setPayable(IPayable* objInFocus) {
	this->objInFocus = objInFocus;
	log("create listener");
	actListener = EventListenerKeyboard::create();
	setKeyListener(&Player::onKeyPressedAct, actListener);
}
