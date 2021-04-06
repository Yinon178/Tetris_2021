#include "Zshape.h"


// ctor
Zshape::Zshape(Board &_boardGame) : Shape(_boardGame)
{
	body[0].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2), boardGame.gameZone.top, true, getSerialObj());
	body[1].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 1, boardGame.gameZone.top, true, getSerialObj());
	body[2].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 1, boardGame.gameZone.top + 1, true, getSerialObj());
	body[3].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2) + 2, boardGame.gameZone.top + 1, true, getSerialObj());
}

//move
AllAdjustRotations Zshape::getPossibleRotations() {
	AllAdjustRotations possibleRotations = AllAdjustRotations(
		{ 
			{Point(2, -1),Point(1, 0),Point(0, -1),Point(-1, 0) },
			{Point(-2, 1),Point(-1, 0),Point(0, 1),Point(1, 0) },
			{Point(2, -1),Point(1, 0),Point(0, -1),Point(-1, 0) },
			{Point(-2, 1),Point(-1, 0),Point(0, 1),Point(1, 0) } 
		}
	);
	return possibleRotations;
}
