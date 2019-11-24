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
	
	moveListener = EventListenerKeyboard::create();
	setKeyListener(&Player::onMoveKeyPressed, moveListener);
	GameTime::addMoveableObject(this);
	setCamera();

	actListener = nullptr;
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

	if (deleteListener) {
		dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->removeKeyEventListener(actListener);
		deleteListener = false;
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

/*
=====================================================================================================
Player key act
=====================================================================================================
*/




void Player::onKeyPressedAct() {
	actListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			objInFocus->pay(this->money);
		}
	};
	actListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {};
}


void Player::setSelectKeys() {
	CitizenController* citizenController = CitizenController::getInstance();


	
	actListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			citizenController->setNewRole(SprTag::BUILDER, objInFocus);
			objInFocus = nullptr;
			deleteListener = true;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			objInFocus->pay(this->money);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			objInFocus->pay(this->money);
		}
	};

	actListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {};
}



void Player::setSelectRoleListener() {
	setKeyListener(&Player::setSelectKeys, actListener);
}

void Player::removeFocusActListener() {
	if (objInFocus != nullptr) {
		dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->removeKeyEventListener(actListener);

		objInFocus->onChangeFocus();
		objInFocus = nullptr;
	}
}

void Player::removeActListener() {
		dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->removeKeyEventListener(actListener);
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
		actListener = EventListenerKeyboard::create();
		setKeyListener(&Player::onKeyPressedAct, actListener);
	}
}
bool Player::focused() {
	if (objInFocus == nullptr)
		return false;
	else
		return true;
}
