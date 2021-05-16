#pragma once
#include "GameObjects.h"
#include "Special.h"

class Bomb : public Special {
public:
	//ctor
	Bomb(Board &_boardGame) : Special(_boardGame) {
		body.setPoint((boardGame.gameZone.left + boardGame.gameZone.right) / 2, boardGame.gameZone.top, true, getSerialObj(), Sign::B);
	}

	//draw
	void draw(char ch = '#')const override;
    
    CLONEABLE(Bomb)
	
	// move
	bool move(char keyPressed = DEFAULT, bool mark = true) override;

	bool explode(int x, int y, bool mark, int& addScore);

	bool isBomb() override { return true; };


};
