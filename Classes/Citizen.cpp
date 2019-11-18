#include"Citizen.h"

Citizen::Citizen(Vec2 pos){
	spr = Sprite::create(CITIZEN);
	spr->setPosition(pos);
	spr->setAnchorPoint(Vec2(0, 0));
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);
}