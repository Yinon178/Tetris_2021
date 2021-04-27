#include "Plus.h"


//ctor
Plus::Plus(Board &_boadGame) : Shape(_boadGame)
{
	body[0].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) - 1, boardGame.gameZone.top + 1, true, getSerialObj());
	body[1].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2), boardGame.gameZone.top, true, getSerialObj());
	body[2].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2), boardGame.gameZone.top + 1, true, getSerialObj());
	body[3].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 1, boardGame.gameZone.top + 1, true, getSerialObj());
}

AllAdjustRotations Plus::getPossibleRotations() const {
	AllAdjustRotations possiblePermutations = AllAdjustRotations(
		{
			{Point(1, -1), Point(0, 1), Point(1, 0), Point(-1, 1) },
			{Point(-1, 1), Point(0, 0), Point(-1, 1), Point(1, -1) },
			{Point(1, -1), Point(0, 0), Point(-1, -1), Point(-1, 1) },
			{Point(-1, 1), Point(0, -1), Point(1, 0), Point(1, -1) }
		}
	);
	return possiblePermutations;
}
