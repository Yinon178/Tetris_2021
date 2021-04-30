#include "Lshape.h"

//ctor
Lshape::Lshape(Board &_boardGame) : Shape(_boardGame)
{
	body[0].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) - 1, boardGame.gameZone.top, true, getSerialObj());
	body[1].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) - 1, boardGame.gameZone.top + 1, true, getSerialObj());
	body[2].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2), boardGame.gameZone.top + 1, true, getSerialObj());
	body[3].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 1, boardGame.gameZone.top + 1, true, getSerialObj());
}

//move
AllAdjustRotations Lshape::getPossibleRotations() const {
	AllAdjustRotations possiblePermutations = AllAdjustRotations(
		{
			{Point(2, 0),Point(1, -1),Point(0, 0),Point(-1, 1) },
			{Point(0, 2),Point(1, 1),Point(0, 0),Point(-1, -1) },
			{Point(-2, 0),Point(-1, 1),Point(0, 0),Point(1, -1) },
			{Point(0, -2),Point(-1, -1),Point(0, 0),Point(1, 1) }
		}
	);
	return possiblePermutations;
}
