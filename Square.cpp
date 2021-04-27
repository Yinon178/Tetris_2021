#include "Square.h"


// ctor 
Square::Square(Board &_boardGame) : Shape(_boardGame)
{
	body[0].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2), boardGame.gameZone.top, true, getSerialObj());
	body[1].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 1, boardGame.gameZone.top, true, getSerialObj());
	body[2].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2), boardGame.gameZone.top + 1, true, getSerialObj());
	body[3].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 1, boardGame.gameZone.top + 1, true, getSerialObj());
}
AllAdjustRotations Square::getPossibleRotations() const {
	AllAdjustRotations possiblePermutations = AllAdjustRotations(
		{
			{Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0) }
		}

	);
	return possiblePermutations;
}

