#pragma once

#include "GameObjects.h"
#include "Shape.h"

class Line : public Shape {
public:

	//ctor
	Line(Board &_boardGame);

	AllAdjustRotations getPossibleRotations() override;

};


