#include <Player.h>
Sprite* spr;
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

	auto follow = Follow::create(spr, Rect::ZERO);
	Enviroment::getInstance()->getScene()->addChild(spr, PLAYER_Z_ORDER);
	Enviroment::getInstance()->getScene()->runAction(follow);
	
	listener = EventListenerKeyboard::create();
	setKeyListener();
	GameTime::addMoveableObject(this);

	player = this;
}

Player* Player::getInstance() {
	if (player)
		return player;
	player = new Player(PLAYER);
	return player;
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

void Player::setKeyListener() {
	onMoveKeyPressed();
	static_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(listener, spr);
}

void Player::onMoveKeyPressed(){

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		changeMoveDirection(keyCode, true);
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

	}
}