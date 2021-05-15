#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Zshape : public Shape {
public:

	//ctor
	Zshape(Board &_boardGame);
    
    CLONEABLE(Zshape)

	AllAdjustRotations getPossibleRotations() const;
};
