#include "UI.h"

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
		tmp->setPosition(
			Vec2(selectSprsPositionX->top() , 
				SELECT_SITIZEN_ROLE_Y ));
		selectSprsPositionX->pop();

		currentCitizen->getSpr()->addChild(tmp);
	}

}


void UI::removeCitizenSelectIcons() {
	if(currentCitizen != nullptr)
		currentCitizen->getSpr()->removeAllChildren();
	currentCitizen = nullptr;
}
