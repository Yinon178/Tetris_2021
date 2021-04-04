#include "Joker.h"

Joker::Joker() : Special()
{
	body.setPoint((boardGame.gameZone.left + boardGame.gameZone.right) / 2, boardGame.gameZone.top, true, getSerialObj(), Sign::J);
	prevJ.setPoint((boardGame.gameZone.left + boardGame.gameZone.right) / 2, boardGame.gameZone.top, false, getSerialObj(), Sign::J);
}

void Joker::draw(char ch) const
{
	body.draw('O');
}

bool Joker::move(Board & boardGame, char keyPressed)
{
	int addScore;

			if (body.gety() == boardGame.gameZone.bottom && keyPressed != LEFT && keyPressed != RIGHT)
				prevJ.setPoint(prevJ.getx(), prevJ.gety(), false, prevJ.getSerialNumber(), prevJ.getSign());

			if (prevJ.isBusy() && keyPressed != JSTOP)
				boardGame.turnOnPoint(prevJ.getx(), prevJ.gety(), prevJ.getSerialNumber(), prevJ.getSign());

			switch (keyPressed)
			{
			case eKEYS::DEFAULT:
				if (body.gety() < boardGame.gameZone.bottom)
				{
					if (!(prevJ.isBusy()))
						boardGame.turnOffPoint(body.getx(), body.gety());

					prevJ.setPoint(body.getx(), body.gety() + 1, (!(boardGame.isValid(body.getx(), body.gety() + 1))),
						boardGame.getSerial(body.getx(), body.gety() + 1), boardGame.getSign(body.getx(), body.gety() + 1));
					boardGame.turnOnPoint(body.getx(), body.gety() + 1, body.getSerialNumber(), Sign::J);
					body.setPoint(body.getx(), body.gety() + 1, true, body.getSerialNumber(), Sign::J);
				}
				else {
					if (boardGame.cleanLines(body.gety()))
						boardGame.updateBoard();
					return false;
				}
				break;
			case eKEYS::LEFT:
				if (boardGame.gameZone.left < body.getx())
				{
					if (!(prevJ.isBusy()))
						boardGame.turnOffPoint(body.getx(), body.gety());
					prevJ.setPoint(body.getx() - 1, body.gety(), (!(boardGame.isValid(body.getx() - 1, body.gety()))),
						boardGame.getSerial(body.getx() - 1, body.gety()), boardGame.getSign(body.getx() - 1, body.gety()));
					boardGame.turnOnPoint(body.getx() - 1, body.gety(), body.getSerialNumber(), Sign::J);
					body.setPoint(body.getx() - 1, body.gety(), true, body.getSerialNumber(), Sign::J);
				}
				break;
			case eKEYS::RIGHT:
				if (boardGame.gameZone.right > body.getx())
				{
					if (!(prevJ.isBusy()))
						boardGame.turnOffPoint(body.getx(), body.gety());

					prevJ.setPoint(body.getx() + 1, body.gety(), (!(boardGame.isValid(body.getx() + 1, body.gety()))),
						boardGame.getSerial(body.getx() + 1, body.gety()), boardGame.getSign(body.getx() + 1, body.gety()));
					boardGame.turnOnPoint(body.getx() + 1, body.gety(), body.getSerialNumber(), Sign::J);
					body.setPoint(body.getx() + 1, body.gety(), true, body.getSerialNumber(), Sign::J);
				}
				break;
			case eKEYS::JSTOP:
				prevJ.setPoint(body.getx(), body.gety(), true, body.getSerialNumber()),
					boardGame.getSign(body.getx(), body.gety());

				if (boardGame.cleanLines(body.gety()))
					boardGame.updateBoard();

				return false;
				break;
			}
			return true;

}
