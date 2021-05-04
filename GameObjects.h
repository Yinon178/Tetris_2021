#pragma once
#include <iostream>
#include <conio.h>
#include "Board.h"
#include "Point.h"


#define BASE_CLONEABLE(Type) \
    virtual Type *clone() const = 0;

#define CLONEABLE(Type) \
    virtual Type *clone() const { return new Type(*this); }

class GameObjects {

protected:
	int serial = 0;
    Board boardGame;
    

public:
	
    GameObjects(int _serial, Board &_boardGame) : serial(_serial), boardGame(_boardGame) {};

	GameObjects() {};

	int getSerialObj() const{ return serial; };

	virtual void draw(char ch = '#')const = 0;

	virtual bool move(char keyPressed = DEFAULT) = 0;

	virtual void updateShape(char direction) = 0;
    
    BASE_CLONEABLE(GameObjects);
    
    void setBoard(Board const &boardGame) {boardGame = Board(boardGame);};

	void setSerialNumber(int _serial) {
		serial = _serial;
	}

};
