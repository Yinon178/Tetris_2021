#pragma once
#include <vector>

#include "GameObjects.h"

enum adjust { HORIZON = 0, VERTICAL = 1, UPSIDE_DOWN = 2, UPSIDE_LEFT = 3};

enum startVal {
	X_SQ = ((10 + 21) / 2), Y_SQ = 5,
	X_ROW = (10 + 21) / 2 - 1, Y_ROW = 5
};

using AdjustRotations = std::vector<Point>;
using AllAdjustRotations = std::vector<AdjustRotations>;

class Shape : public GameObjects {
protected:
	enum { SIZE = 4 };
	Point body[SIZE];
	int adjust = HORIZON;
public:
	Board& boardGame;
	AdjustRotations left = { Point(-1, 0), Point(-1, 0) , Point(-1, 0),  Point(-1, 0) };
	AdjustRotations def = { Point(0, 1), Point(0, 1) ,Point(0, 1),  Point(0, 1) };
	AdjustRotations right = { Point(1, 0), Point(1, 0) , Point(1, 0),  Point(1, 0) };
	//ctor
	Shape(int _serial, Board& _boardGame) : GameObjects(_serial), boardGame(_boardGame) {};
	Shape(Board& _boardGame) : GameObjects(), boardGame(_boardGame) {};

    
	virtual void draw(char ch = '#')const;

	bool move(Board& boardGame, char keyPressed = DEFAULT);
	void updateShape(char direction);

	bool moveByDelta(Board& boardGame, char keyPressed, AdjustRotations currentMove, int direction);

	//Pure Virtual
	virtual void rotate(int direction = 1);

	virtual AllAdjustRotations getPossibleRotations() = 0;


};
