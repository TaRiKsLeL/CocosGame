#include "Collisions.h"

void Collisions::playerCollide(Player* player, Node* nodeA, Node* nodeB) {

	Node* nodeRes;

	if (nodeA->getTag() == SprTag::PLAYER)
		nodeRes = nodeB;
	else
		nodeRes = nodeA;

	switch (nodeRes->getTag())
	{
	case SprTag::BUILDER:
		break;
	case SprTag::CITIZEN:
		break;
	case SprTag::SLAVE_TRAIDER:
		break;
	case SprTag::WARRIOR:
		break;
	case SprTag::WORKER:
		break;
	};
}
