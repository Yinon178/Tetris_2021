#pragma once

#include "GameObjects.h"

class Special : public GameObjects {
protected:
	//data member
	Point body;
public:
	Special(Board& _boardGame, int _serial) : GameObjects(_serial, _boardGame) {};
	Special(Board& _boardGame) : GameObjects(_boardGame) {};

	//draw - Pure virtual
	void draw(char ch = '#') const override = 0;
    
    BASE_CLONEABLE(Special)

	//move 
	bool move(char keyPressed = DEFAULT, bool mark = true) = 0;

	//update shape
	virtual void updateShape(char direction) {
		return;
	}

};
