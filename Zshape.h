#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Zshape : public Shape {
public:
	//ctor
	Zshape();

	AllAdjustRotations getPossibleRotations();
};