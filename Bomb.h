#pragma once
#include "GameObjects.h"
#include "Special.h"

class Bomb : public Special {
	int bla = 0;
public:

	//ctor
	Bomb() : Special() {
		body.setPoint((boardGame.gameZone.left + boardGame.gameZone.right) / 2, boardGame.gameZone.top, true, getSerialObj(), Sign::B);
	}

	//draw
	void draw(char ch = '#')const override;
	
	// move
	bool move(Board &boardGame, char keyPressed = DEFAULT) override;


};
