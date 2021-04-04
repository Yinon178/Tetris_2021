#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Square : public Shape {
public:
    Square(Board &_boardGame); // ctor

	//move
	bool move(char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override { 
		return;
	}

};
