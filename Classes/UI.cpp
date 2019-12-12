#include "UI.h"
#include "MainMenu.h"

UI* UI::ui;

UI::UI() {
	selectSprs = nullptr;
	selectSprsPositionX = nullptr;
}

void UI::initIcons() {
	if(selectSprs != nullptr)
		delete selectSprs;

	selectSprs = new vector<Sprite*>{
		Sprite::create(PICK_SPR),
		Sprite::create(HUMMER_SPR),
		Sprite::create(BOW_SPR)
	};


}

/*
=====================================================================================================
GAME OVER
=====================================================================================================
*/

void UI::setGameOverSprite(string name)
{
	gameOverSprite = Sprite::create(name);
	gameOverSprite->setPosition(Vec2(CUST_OFFSET*3, -CAMERA_OFFSET_Y+CUST_OFFSET));
	gameOverSprite->setScale(SCALE_FACTOR);
	gameOverSprite->getTexture()->setAliasTexParameters();

	auto back = Sprite::create(GAME_OVER_BACK_SPR);
	back->setOpacity(GAME_OVER_BACK_OPACITY);


	Player::getInstance()->addChild(back);
	Player::getInstance()->addChild(gameOverSprite);
	Player::getInstance()->removeAllListeners();

	initMainSceneListener();

}

void UI::initMainSceneListener()
{
	toMainSceneListener = EventListenerKeyboard::create();

	toMainSceneListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:

			Director::getInstance()->replaceScene(MainMenu::createScene());
			break;
		default:
			break;
		}
	};

	dynamic_cast<GameScene*>(Enviroment::getInstance()->getScene())->setKeyEventListener(toMainSceneListener,gameOverSprite);
}


UI* UI::getInstance() {
	if (ui != nullptr)
		return ui;
	ui = new UI();
	ui->selectSprsPositionX = new stack<int>();
	return ui;
}
/*
=====================================================================================================
CITIZEN PICTURES
=====================================================================================================
*/




void UI::initStack() {

	selectSprsPositionX->push(SELECT_SITIZEN_ROLE_RIGHT_X);
	selectSprsPositionX->push(SELECT_SITIZEN_ROLE_MIDDLE_X);
	selectSprsPositionX->push(SELECT_SITIZEN_ROLE_LEFT_X);
}
/*
=====================================================================================================
CITIZEN PICTURES METHODS
=====================================================================================================
*/



void UI::addCitizenSelectIcons(Citizen* citizen) {
	
	currentCitizen = citizen;
	initStack();
	initIcons();

	for (Sprite* tmp : *selectSprs) {
		tmp->setAnchorPoint(Vec2(0.5, 0));
		tmp->getTexture()->setAliasTexParameters();
		tmp->setPosition(
			Vec2(selectSprsPositionX->top() + currentCitizen->getBoundingBox().size.width/2,
				SELECT_SITIZEN_ROLE_Y ));
		selectSprsPositionX->pop();

		currentCitizen->addChild(tmp);
	}

}

void UI::addMark(Sprite* spr) {
	Sprite* mark = Sprite::create(MARK_ICO_SPR);
	mark->getTexture()->setAliasTexParameters();
	mark->setAnchorPoint(Vec2(0.5, 0));
	mark->setPosition(spr->getContentSize().width / 2, spr->getContentSize().height / 2 + MARKS_Y_SHIFT);
	spr->addChild(mark);
}
void UI::addHummer(Sprite* spr) {
	Sprite* mark = Sprite::create(HUMMER_ICO_SPR);
	mark->setAnchorPoint(Vec2(0.5, 0));
	mark->getTexture()->setAliasTexParameters();
	mark->setPosition(spr->getContentSize().width / 2, spr->getContentSize().height / 2 + MARKS_Y_SHIFT);
	spr->addChild(mark);
}
Sprite* UI::getSelector(Sprite* spr) {
	Sprite* mark = Sprite::create(SELECTOR_ICO_SPR);
	mark->getTexture()->setAliasTexParameters();
	mark->setAnchorPoint(Vec2(0.5, 0));
	mark->setPosition(spr->getContentSize().width / 2, spr->getContentSize().height / 2 + SELECTOR_Y_SHIFT);
	spr->addChild(mark);
	return mark;
}


void UI::removeCitizenSelectIcons() {
	if(currentCitizen != nullptr)
		currentCitizen->removeAllChildren();
	currentCitizen = nullptr;
}

/*
=====================================================================================================
ANIMATE
=====================================================================================================
*/

Animate* UI::createAnimate(string path, int imAmount, float imSize, int height, float time)
{
	Vector<SpriteFrame*> picsVector;
	picsVector.reserve(imAmount);
	for (int i = 0; i < imAmount; i++) {
		picsVector.pushBack(SpriteFrame::create(path, Rect(i * imSize, imSize-height, imSize, height)));
		picsVector.at(i)->getTexture()->setAliasTexParameters();
	}
	auto animation = Animation::createWithSpriteFrames(picsVector, time, -1);
	Animate* animate = Animate::create(animation);
	animate->retain();

	return animate;
}


/*
=====================================================================================================
COIN
=====================================================================================================
*/

Label* UI::getCoinsLabel()
{
	return coinsAmount;
}

void UI::createCoinsLabel(std::string text, std::string font, int size)
{
	coinsAmount = Label::createWithTTF(text, font, size);
	coinsAmount->setScale(1.0f / LABEL_SCALE);
	coinsAmount->setPosition(Vec2(LABEL_X_SPACE_FROM_PLAYER +CUST_OFFSET*2, LABEL_Y_SPACE_FROM_PLAYER));
	coinsAmount->getFontAtlas()->setAliasTexParameters();
	Player::getInstance()->addChild(coinsAmount);
}

void UI::createVignette(string spr, int opacity)
{
	auto sp = Sprite::create(spr);
	sp->setOpacity(opacity);
	sp->setPositionY(-CAMERA_OFFSET_Y);
	sp->setPositionX(CUST_OFFSET*2);
	sp->setScale(SCALE_FACTOR*1.2);
	Player::getInstance()->addChild(sp);
}

void UI::setCoinsAmountLabel(int sum)
{
	coinsAmount->setString(to_string(sum));
}

void UI::createCoin(string path, int imAmount, float imSize, float time) {
	coin = Sprite::create(path);
	coin->setPosition(Vec2(LABEL_X_SPACE_FROM_PLAYER, LABEL_Y_SPACE_FROM_PLAYER));
	coin->setScale(COIN_SCALE_FACTOR);
	coin->runAction(createAnimate(path, imAmount, imSize, imSize, time));
	Player::getInstance()->addChild(coin);
}

Sprite* UI::getCoinSprite() {
	return coin;
}

/*
=====================================================================================================
HP
=====================================================================================================
*/

void UI::createHeart(std::string fullHeartPath, std::string emptyHeartPath, int am, float size, float time)
{
	fullHeart = Sprite::create(fullHeartPath);
	fullHeart->setPosition(Vec2(-LABEL_X_SPACE_FROM_PLAYER + CUST_OFFSET*1.5, LABEL_Y_SPACE_FROM_PLAYER - (CUST_OFFSET / 2)));
	fullHeart->setAnchorPoint(Vec2(0.5, 0));
	fullHeart->runAction(createAnimate(fullHeartPath, am, size, size, time));

	emptyHeart = Sprite::create(emptyHeartPath);
	emptyHeart->setPosition(Vec2(-LABEL_X_SPACE_FROM_PLAYER + CUST_OFFSET * 1.5, LABEL_Y_SPACE_FROM_PLAYER- (CUST_OFFSET / 2)));
	emptyHeart->setAnchorPoint(Vec2(0.5, 0));
	emptyHeartAnimate = createAnimate(emptyHeartPath, am, size, size, time);
	emptyHeart->runAction(emptyHeartAnimate);

	Player::getInstance()->addChild(emptyHeart);
	Player::getInstance()->addChild(fullHeart);

}

void UI::updateHeartLogo(int hpVal)
{
	int pixelsToShow = static_cast<int>(HEART_IMAGE_SIZE*((float)hpVal / (float)PLAYER_MAX_HEALTH));

	emptyHeart->stopAllActions();
	fullHeart->stopAllActions();
	fullHeart->setPosition(Vec2(fullHeart->getPositionX(), fullHeart->getPositionY()));
	fullHeart->runAction(createAnimate(FULL_HEART_FRAMES, HEART_IMAGES_AMOUNT, HEART_IMAGE_SIZE, pixelsToShow, HEART_TIME_PER_FRAME));
	emptyHeart->runAction(emptyHeartAnimate);

	log("%d", pixelsToShow);
}
