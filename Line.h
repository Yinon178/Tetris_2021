#pragma once

#include "GameObjects.h"
#include "Shape.h"

class Line : public Shape {
public:
	//ctor
	Line();

	AllAdjustRotations getPossibleRotations() override;
};


