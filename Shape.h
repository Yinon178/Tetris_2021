#pragma once

#include "GameObjects.h"
#include <vector>

enum adjust { HORIZON = 0, VERTICAL = 1, UPSIDE_DOWN = 2, UPSIDE_LEFT = 3};

enum startVal {
	X_SQ = ((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2), Y_SQ = Board::GameZone::TOP,
	X_ROW = (Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 - 1, Y_ROW = Board::GameZone::TOP
};

using AdjustRotations = std::vector<Point>;
using AllAdjustRotations = std::vector<AdjustRotations>;

class Shape : public GameObjects {
protected:
	enum { SIZE = 4 };
	Point body[SIZE];
	int adjust = HORIZON;

public:
	AdjustRotations left = { Point(-1, 0), Point(-1, 0) , Point(-1, 0),  Point(-1, 0) };
	AdjustRotations def = { Point(0, 1), Point(0, 1) ,Point(0, 1),  Point(0, 1) };
	AdjustRotations right = { Point(1, 0), Point(1, 0) , Point(1, 0),  Point(1, 0) };

	//ctor
	Shape(int _serial) : GameObjects(_serial) {};

	Shape() : GameObjects() {} ; //empty ctor

	virtual void draw(char ch = '#')const;

	bool move(Board &boardGame, char keyPressed = DEFAULT);

	void updateShape(char direction);

	bool moveByDelta(Board& boardGame, char keyPressed, AdjustRotations currentMove, int direction);

	//Pure Virtual
	virtual void rotate(int direction = 1);

	virtual AllAdjustRotations getPossibleRotations() = 0;


};