#include "Line.h"


//ctor
Line::Line(Board &_boardGame) : Shape(_boardGame)
{
	body[0].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2 ), boardGame.gameZone.top, true, getSerialObj());
	body[1].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2 ), boardGame.gameZone.top + 1, true, getSerialObj());
	body[2].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2 ), boardGame.gameZone.top + 2, true, getSerialObj());
	body[3].setPoint(((boardGame.gameZone.left + boardGame.gameZone.right) / 2 ), boardGame.gameZone.top + 3, true, getSerialObj());
}

//move Line
AllAdjustRotations Line::getPossibleRotations() {
	AllAdjustRotations possiblePermutations = AllAdjustRotations(
		{
			{Point(-1, 2), Point(0,1),  Point(1,0),   Point(2, -1) },
			{Point(2, -2), Point(1,-1), Point(0,0),   Point(-1,1) },
			{Point(-2, 1), Point(-1,0), Point(0,-1),  Point(1,-2)},
			{Point(1, -1), Point(0, 0), Point(-1, 1), Point(-2, 2) }
		}
	);
	return possiblePermutations;
}

