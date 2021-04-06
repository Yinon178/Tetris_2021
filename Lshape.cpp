#include "Lshape.h"

//ctor
Lshape::Lshape(Board &_boardGame) : Shape(_boardGame)
{
	body[0].setPoint(X_SQ - 1, Y_SQ, true, getSerialObj());
	body[1].setPoint(X_SQ - 1, Y_SQ + 1, true, getSerialObj());
	body[2].setPoint(X_SQ, Y_SQ + 1, true, getSerialObj());
	body[3].setPoint(X_SQ + 1, Y_SQ + 1, true, getSerialObj());
}

//move
AllAdjustRotations Lshape::getPossibleRotations() {
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
