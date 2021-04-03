#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Plus : public Shape {
public:
	//ctor
	Plus();

	AllAdjustRotations getPossibleRotations();
};