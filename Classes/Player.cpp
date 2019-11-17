#include <Player.h>

Player* Player::player{ nullptr };

Player::Player(const std::string fileName) {
	spr = Sprite::create(fileName);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(Vec2(PLAYER_START_X, PLAYER_START_Y));
	
	Enviroment::getInstance()->getScene()->addChild(spr, PLAYER_Z_ORDER);
	
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

void Player::move() {
	Vec2 pos = spr->getPosition();

	if (direction.right) {
		pos.x += PLAYER_SPEED;
	}
	else if (direction.left) {
		pos.x -= PLAYER_SPEED;
	}

	spr->setPosition(pos);
}

void Player::setKeyListener() {
	onKeyMove();
	static_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(listener, spr);
}

void Player::onKeyMove(){

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		setMoveKeys(keyCode, true);
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		setMoveKeys(keyCode, false);
	};
}
void Player::onKeyPressedAct(){

}

void Player::setMoveKeys(EventKeyboard::KeyCode keyCode, bool condition) {
	
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		direction.right = condition;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		direction.left = condition;
		break;
	}

}
void Player::setActKeys(EventKeyboard::KeyCode keyCode){
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {

	}
}