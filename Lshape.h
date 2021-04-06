#pragma once
#include "Shape.h"

class Lshape : public Shape {
public:
	//ctor
	Lshape(Board &_boardGame);

	AllAdjustRotations getPossibleRotations();
};
