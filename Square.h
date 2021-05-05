#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Square : public Shape {
public:
    Square(Board &_boardGame); // ctor

    CLONEABLE(Square)

    AllAdjustRotations getPossibleRotations() const;
};
