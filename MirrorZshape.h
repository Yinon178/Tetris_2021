#pragma once
#include "GameObjects.h"
#include "Shape.h"

class MirrorZshape : public Shape {
public:

	//ctor
	MirrorZshape(Board &_boardGame);
    
    CLONEABLE(MirrorZshape)
    
	AllAdjustRotations getPossibleRotations() const;
};

