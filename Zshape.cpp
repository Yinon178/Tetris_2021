#include "Zshape.h"


// ctor
Zshape::Zshape()
{
	body[0].setPoint(X_SQ, Y_SQ, true, getSerialObj());
	body[1].setPoint(X_SQ + 1, Y_SQ, true, getSerialObj());
	body[2].setPoint(X_SQ + 1, Y_SQ + 1, true, getSerialObj());
	body[3].setPoint(X_SQ + 2, Y_SQ + 1, true, getSerialObj());
}

AllAdjustRotations Zshape::getPossibleRotations() {
	AllAdjustRotations possibleRotations = AllAdjustRotations(
		{ {Point(2, -1),Point(1, 0),Point(0, -1),Point(-1, 0) },
	{Point(-2, 1),Point(-1, 0),Point(0, 1),Point(1, 0) },
	{Point(2, -1),Point(1, 0),Point(0, -1),Point(-1, 0) },
	{Point(-2, 1),Point(-1, 0),Point(0, 1),Point(1, 0) }
		}
	);
	return possibleRotations;
}
