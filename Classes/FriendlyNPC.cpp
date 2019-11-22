#include "FriendlyNPC.h"
#include"Enviroment.h"


FriendlyNPC::FriendlyNPC(Vec2 pos, std::string sprName) {
	spr = Sprite::create(sprName);
	spr->setPosition(pos);
	spr->setAnchorPoint(Vec2(0, 0));
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);
}


void FriendlyNPC::setUnactive() {
	isActive = false;
}

void FriendlyNPC::setActive() {
	isActive = true;
}