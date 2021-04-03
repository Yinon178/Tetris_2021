#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Square : public Shape {
public:
	// ctor
	Square(); 

	AllAdjustRotations getPossibleRotations();
};