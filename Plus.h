#pragma once
#include "GameObjects.h"
#include "Shape.h"


class Plus : public Shape {
public:

	//ctor
	Plus(Board &_boadGame);
    
    CLONEABLE(Plus)

	AllAdjustRotations getPossibleRotations() const;
};
