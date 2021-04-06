#include "Line.h"


//ctor
Line::Line(Board &_boardGame) : Shape(_boardGame)
{
	for (int i = 0; i < SIZE; i++)
		body[i].setPoint(X_ROW + i, Y_ROW, true, getSerialObj());
}

//move Line
AllAdjustRotations Line::getPossibleRotations() {
	AllAdjustRotations possiblePermutations = AllAdjustRotations(
		{
			{Point(1, -1), Point(0, 0), Point(-1, 1), Point(-2, 2) },
			{Point(-1, 2), Point(0,1),  Point(1,0),   Point(2, -1) },
			{Point(2, -2), Point(1,-1), Point(0,0),   Point(-1,1) },
			{Point(-2, 1), Point(-1,0), Point(0,-1),  Point(1,-2)}
		}
	);
	return possiblePermutations;
}

