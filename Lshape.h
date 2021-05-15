#pragma once
#include "Shape.h"

class Lshape : public Shape {
public:
	//ctor
	Lshape(Board &_boardGame);
    
    CLONEABLE(Lshape)

	AllAdjustRotations getPossibleRotations() const;
};
