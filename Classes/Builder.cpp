#include "Builder.h"

Builder::Builder(Vec2 pos) : FriendlyNPC(pos, BUILDER_SPR) {}

void Builder::setBuild(bool isBuilding) {
	this->m_isBuilding = isBuilding;
}

bool Builder::isBuilding() {
	return m_isBuilding;
}