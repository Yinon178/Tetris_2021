#pragma once
#include "GameObjects.h"
#include "Shape.h"


class Plus : public Shape {
public:

	//ctor
	Plus(Board &_boadGame);

	//move
	bool move(char keyPressed = DEFAULT) override;

	//rotate
	void rotate() override;

};
