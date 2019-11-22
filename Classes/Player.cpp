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
	spr->setPosition(Vec2(PLAYER_START_X, PLAYER_START_Y));
	spr->addComponent(createPhysBody());

	Follow* follow = Follow::create(spr, Rect::ZERO);
	Enviroment::getInstance()->getScene()->addChild(spr, PLAYER_Z_ORDER);
	Enviroment::getInstance()->getScene()->runAction(follow);


	
	listener = EventListenerKeyboard::create();
	setKeyListener(&Player::onMoveKeyPressed);
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
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size, PhysicsMaterial(1,1,1));
	pb->setTag(SprTag::PLAYER);
	//pb->setDynamic(false);
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

void Player::setKeyListener(void (Player::*moveFuncPointer)()) {
	(*this.*moveFuncPointer)();
	static_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(listener, spr);
}

void Player::onMoveKeyPressed(){

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, true);
		if (objInFocus)
			setActKeys(keyCode);
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
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

}

void Player::setActKeys(EventKeyboard::KeyCode keyCode){
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		objInFocus->pay(this->money);
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

void Player::setPayable(IPayable* objInFocus) {
	this->objInFocus = objInFocus;
	//setKeyListener(&Player::onMoveKeyPressed);
}
