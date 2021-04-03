#pragma once
#include "Shape.h"

class Lshape : public Shape {
public:
	//ctor
	Lshape();

	AllAdjustRotations getPossibleRotations();
};