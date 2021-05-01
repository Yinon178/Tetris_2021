#pragma once
#include <iostream>
#include <conio.h>
#include "Board.h"
#include "Point.h"


class GameObjects {

protected:
	int serial = 0;

public:
	
	GameObjects(int _serial) {
		serial = _serial;
	}

	GameObjects() {};

	int getSerialObj() const{ return serial; };

	virtual void draw(char ch = '#')const = 0;

	virtual bool move(char keyPressed = DEFAULT) = 0;

	virtual void updateShape(char direction) = 0;
    
    virtual GameObjects *clone () = 0;

	void setSerialNumber(int _serial) {
		serial = _serial;
	}

};
