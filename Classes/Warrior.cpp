#include "Warrior.h"

Warrior::Warrior(Vec2 pos) : FriendlyNPC(pos, WARRIOR_SPR) {
	spr->setTag(SprTag::WARRIOR);
}
