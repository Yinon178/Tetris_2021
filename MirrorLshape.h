#pragma once
#include "Shape.h"

class MirrorLshape : public Shape {
public:
	//ctor
	MirrorLshape(Board& _boardGame);
    
    CLONEABLE(MirrorLshape)

	AllAdjustRotations getPossibleRotations() const;
};
