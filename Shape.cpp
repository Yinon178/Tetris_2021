#include "Shape.h"

void Shape::draw(char ch)const
{}

bool Shape::move(char keyPressed, bool mark)
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
        currentMove = possibleRotations[(adjust + possibleRotations.size() - 1) % possibleRotations.size()];
        direction = -1;
        break;
    case eKEYS::HARD_DOWN:
        while (true)
        {
            if (!(move( DEFAULT, mark)))
                break;
            if (mark)
                boardGame.updateScoreBoard(2); // hard_drop x2 Distance 
        }
        return true;
        break;
    default:
        currentMove = def;
        break;
    }
    return moveByDelta( keyPressed, currentMove, direction, mark);

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
        this->adjust = (this->adjust + possibleRotations.size() - 1) % possibleRotations.size();
    }
}


bool Shape::moveByDelta( char keyPressed, AdjustRotations currentMove, int direction, bool mark) {
    bool validMovement = true;
    for (int i = 0; i < SIZE; i++)
    {
        int newX = (body[i].getx() + currentMove[i].getx() * direction);
        int newY = (body[i].gety() + currentMove[i].gety() * direction);
        if (boardGame.isValid(newX, newY) == false && boardGame.getSerial(newX, newY) != this->getSerialObj())
        {
            validMovement = false;
            if (keyPressed == LEFT || keyPressed == RIGHT) { // wall encountered
                keyPressed = DEFAULT;
                return move(keyPressed, mark);
                 
            }
            else {
                if (boardGame.cleanLines(body[i].gety(), mark))
                {
                    boardGame.updateBoard(mark);
                }
            }
        }
    }
    if (!validMovement)
        return validMovement;
    for (int i = 0; i < SIZE; i++)
    {
        boardGame.turnOffPoint(body[i].getx(), body[i].gety(), mark);
    }
    for (int i = 0; i < SIZE; i++)
    {
        int newX = (body[i].getx() + currentMove[i].getx() * direction);
        int newY = (body[i].gety() + currentMove[i].gety() * direction);

        boardGame.turnOnPoint(newX, newY, getSerialObj(), '#', mark);
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
        for (Point& p : body)
            p.setPoint(p.getx(), p.gety() + 1, true, p.getSerialNumber());
		break;
	}

}
