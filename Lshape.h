#pragma once
#include "Shape.h"

class Lshape : public Shape {
public:
	//ctor
	Lshape(Board &_boardGame);

	//move
	bool move(char keyPressed = DEFAULT) override;
	
	//rotate
	void rotate() override;
};
