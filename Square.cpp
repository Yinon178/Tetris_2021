#include "Square.h"


// ctor 
Square::Square() : Shape()
{
	body[0].setPoint(X_SQ, Y_SQ, true, getSerialObj());
	body[1].setPoint(X_SQ + 1, Y_SQ, true, getSerialObj());
	body[2].setPoint(X_SQ, Y_SQ + 1, true, getSerialObj());
	body[3].setPoint(X_SQ + 1, Y_SQ + 1, true, getSerialObj());
}


AllAdjustRotations Square::getPossibleRotations() {
	AllAdjustRotations possiblePermutations = AllAdjustRotations(
		{
			{Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0) }
		}
	);
	return possiblePermutations;
}
