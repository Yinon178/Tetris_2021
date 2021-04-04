#pragma once

#include "GameObjects.h"
#include "Shape.h"

class Line : public Shape {
public:

	//ctor
	Line(Board &_boardGame);

	//move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override;

};


