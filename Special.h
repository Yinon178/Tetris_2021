#pragma once

#include "GameObjects.h"

class Special : public GameObjects {
protected:
	//data member
	Point body;
public:
	Board& boardGame;
	Special(Board& _boardGame, int _serial) : GameObjects(_serial), boardGame(_boardGame) {};
	Special(Board& _boardGame) : GameObjects(), boardGame(_boardGame) {};

	//draw - Pure virtual
	void draw(char ch = '#') const override = 0;

	//move 
	bool move(char keyPressed = DEFAULT) = 0;

	//update shape
	virtual void updateShape(char direction) {
		return;
	}

};