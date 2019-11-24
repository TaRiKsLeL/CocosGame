#include "KingdomBorders.h"

bool KingdomBorders::isInKingdom(float xPos)
{
	if (xPos >= leftX && xPos <= rightX) {
		return true;
	}
	return false;
}
