#pragma once

#include "GameObjects.h"
#include "Special.h"

class Joker : public Special {
private:
	Point prevJ;
public:

	//ctor
	Joker(Board& _boardGame);

	//draw 
	void draw(char ch = '#')const override;

	//move
	bool move(char keyPressed = DEFAULT) override;

};