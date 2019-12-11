#include "Payable.h"
#include "UI.h"

Payable::Payable() : selector(nullptr) {

}


void Payable::setSelectorSpr(Sprite* sprToAdd) {
		selector = UI::getInstance()->getSelector(sprToAdd);
}

void Payable::removeSelector() {
	selector->removeFromParentAndCleanup(true);
	selector = nullptr;
}

bool Payable::selectorIsVisible() {
	if(selector != nullptr)
		return selector->isVisible();
	return false;
}

