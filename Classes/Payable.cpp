#include "Payable.h"
#include "UI.h"

Payable::Payable() : selector(nullptr) {

}


void Payable::setSelectorSpr(Sprite* sprToAdd) {
	if (selector == nullptr) {
		selector = UI::getInstance()->getSelector(sprToAdd);
	}
	else {
		selector->setVisible(true);
		selector->resume();

	}
}

void Payable::removeSelector() {
	selector->setVisible(false);
	selector->pause();
}
