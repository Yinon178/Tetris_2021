#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Zshape : public Shape {
public:

	//ctor
	Zshape(Board &_boardGame);

	AllAdjustRotations getPossibleRotations();
};
