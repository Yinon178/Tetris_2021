#pragma once
#include "GameObjects.h"
#include "Shape.h"

class Zshape : public Shape {
public:

	//ctor
	Zshape(Board &_boardGame);

	//move
	bool move(char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override;
};
