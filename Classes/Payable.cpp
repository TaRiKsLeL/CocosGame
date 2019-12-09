#include "Payable.h"
#include "UI.h"

void Payable::setSelectorSpr(Sprite* sprToAdd) {
	selector = UI::getInstance()->getSelector(sprToAdd);
}

void Payable::removeSelector() {
	if (selector == nullptr)
		return;
	selector->removeFromParentAndCleanup(true);
	selector = nullptr;
}
