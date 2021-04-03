#include "Shape.h"

void Shape::draw(char ch)const
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color,getSerialObj() % 4 + 10);
	for (const Point&p : body)
		p.draw();
}


bool Shape::move(Board& boardGame, char keyPressed)
{
	bool flag = true;
	AdjustRotations currentMove;
	int direction = 1;
	AllAdjustRotations possibleRotations = getPossibleRotations();
	switch (keyPressed) {
	case eKEYS::DEFAULT:
		currentMove = def;
		break;
	case eKEYS::LEFT:
		currentMove = left;
		break;
	case eKEYS::RIGHT:
		currentMove = right;
		break;
	case eKEYS::ROUTE:
		currentMove = possibleRotations[adjust];
		break;
	case eKEYS::ROUTEC:
		currentMove = possibleRotations[(adjust + possibleRotations.size()-1) % possibleRotations.size()];
		direction = -1;
		break;
	case eKEYS::HARD_DOWN:
		while (true)
		{
			if (!(move(boardGame, DEFAULT)))
				break;
			boardGame.updateScoreBoard(2); // hard_drop x2 Distance 
		}
		return true;
		break;
	default:
		currentMove = def;
		break;
	}
	return moveByDelta(boardGame, keyPressed, currentMove, direction);

}
void Shape::rotate(int direction)
{
	AdjustRotations currentRotate;
	AllAdjustRotations possibleRotations = getPossibleRotations();
	if (direction == 1) {
		currentRotate = possibleRotations[adjust];
	}
	else {
		currentRotate = possibleRotations[(adjust + possibleRotations.size() - 1) % possibleRotations.size()];
	}

	for (int i = 0; i < SIZE; i++)
	{
		int newX = (body[i].getx() + currentRotate[i].getx() * direction);
		int newY = (body[i].gety() + currentRotate[i].gety() * direction);
		body[i].setPoint(newX, newY, true, getSerialObj());
	}
	if (direction == 1) {
		this->adjust = (this->adjust + 1) % possibleRotations.size();
	}
	else {
		this->adjust = (this->adjust + possibleRotations.size() -1 ) % possibleRotations.size();
	}
}


bool Shape::moveByDelta(Board& boardGame, char keyPressed, AdjustRotations currentMove, int direction) {
	for (int i = 0; i < SIZE; i++)
	{
		int newX = (body[i].getx() + currentMove[i].getx() * direction);
		int newY = (body[i].gety() + currentMove[i].gety() * direction);
		if (boardGame.isValid(newX, newY) == false && boardGame.getSerial(newX, newY) != this->getSerialObj())
		{
			while (boardGame.cleanLines(body[i].gety() + 1))
			{
				boardGame.updateBoard();
			}
			return false;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		boardGame.turnOffPoint(body[i].getx(), body[i].gety());
	}
	for (int i = 0; i < SIZE; i++)
	{
		int newX = (body[i].getx() + currentMove[i].getx() * direction);
		int newY = (body[i].gety() + currentMove[i].gety() * direction);

		boardGame.turnOnPoint(newX, newY, getSerialObj());
	}
	updateShape(keyPressed);
	return true;

}


void Shape::updateShape(char direction)
{
	switch (direction)
	{
	case eKEYS::DEFAULT:
		for (Point&p : body)
			p.setPoint(p.getx(), p.gety() + 1, true, p.getSerialNumber());
		break;
	case eKEYS::LEFT:
		for (Point&p : body)
			p.setPoint(p.getx() - 1, p.gety(), true, p.getSerialNumber());
		break;
	case eKEYS::RIGHT:
		for (Point&p : body)
			p.setPoint(p.getx() + 1, p.gety(), true, p.getSerialNumber());
		break;
	case eKEYS::ROUTE:
		rotate(1);
		break;
	case eKEYS::ROUTEC:
		rotate(-1);
		break;
	default:
		break;
	}
}
