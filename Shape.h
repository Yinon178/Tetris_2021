#pragma once

#include "GameObjects.h"

enum adjust { HORIZON = 0, VERTICAL = 1, UPSIDE_DOWN = 2, UPSIDE_LEFT = 3};

enum startVal {
	X_SQ = ((10 + 21) / 2), Y_SQ = 5,
	X_ROW = (10 + 21) / 2 - 1, Y_ROW = 5
};

class Shape : public GameObjects {
    Board &boardGame
protected:
	enum { SIZE = 4 };
	Point body[SIZE];
	int adjust = HORIZON;
public:

	//ctor
	Shape(int _serial, Board &_board) : GameObjects(_serial) {board = _board};
	Shape(Board _board) : GameObjects() {board = _board} ;
    
	virtual void draw(char ch = '#')const;

	//Pure Virtual
	virtual bool move(char keyPressed = DEFAULT) = 0;

	virtual void updateShape(char direction);

	//Pure Virtual
	virtual void rotate() = 0;


};
