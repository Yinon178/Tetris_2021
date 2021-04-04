#include "TetrisGame.h"
#include "Joker.h"
#include "Board.h"
#include "Line.h"
#include "Square.h"
#include "Bomb.h"
#include "Plus.h"
#include "Zshape.h"
#include "Lshape.h"


enum {RAND = 7};

enum Type{Single, SQ, R, P, L, Z};

enum Speed {Fast = 130, Normal = 200 };

enum MenuKeys {START = '1', PAUSE = '27', FAST_SPEED = '3', NORMAL_SPEED = '4', EXIT = '9'};

int static serialNumber = 0;


//           <<<RUN>>>
void TetrisGame::run() {

	GameObjects * objectPlayer1;
	int gameSpeed = Normal;
	char keyPressed = 0;
	int type = -1;
	bool gameOver = false, exitGame = false;
	int bestScore = 0;
	int score = 0;


	while (keyPressed != EXIT && !exitGame)
	{
		hideCursor();
		gameSpeed = Speed::Normal;
		if (_kbhit()) // checks if there is anything in the buffer
		{
			keyPressed = _getch();
			if (keyPressed == START)
			{
				if (gameOver) {
					gameOver = false;
					boardGamePlayer1.cleanGameOver();
                    boardGamePlayer2.cleanGameOver();
				}
				if (exitGame == EXIT)
					break;
				while (true)
				{
					while (!gameOver && !exitGame)
					{

						if (!checkGameOver(type))
						{
							gameOver = true;
							break;
						}

						serialNumber++;
						objectPlayer1 = createNewObject(type, boardGamePlayer1);


						while (objectPlayer1->move(this->boardGamePlayer1))
						{
							char keyPressed;
							if (_kbhit()) // checks if there is anything in the buffer
							{
								keyPressed = _getch(); // take the head of the buffer
								if (keyPressed == EXIT) {
									exitGame = true;
									break;
								}
								else if (keyPressed == NORMAL_SPEED)
									gameSpeed = Speed::Normal;
								else if (keyPressed == FAST_SPEED)
									gameSpeed = Speed::Fast;

								if (keyPressed == PAUSE)
								{
									while (true)
									{
										if (_kbhit()) {

											keyPressed = _getch();
											if (keyPressed == PAUSE)
												break;
										}
									}
								}
								if (!(objectPlayer1->move(this->boardGamePlayer1, keyPressed)))
									break;
							}
							Sleep(gameSpeed);

						}
						delete objectPlayer1;



					}
					if (gameOver)
					{
						score = boardGamePlayer1.getScore();
						if (score > bestScore) {
							bestScore = score;
							gotoxy(Board::LEFT_F, Board::BOTTOM_F + 5);
							HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(color, 4);
							cout << "~~NEW RECORD~~";
							SetConsoleTextAttribute(color, 7);
							boardGamePlayer1.updateRecord(bestScore);
						}
						gotoxy(Board::LEFT_F + 2, Board::BOTTOM_F + 1);
						cout << "GAME OVER" << endl;
						gotoxy(Board::LEFT_F - 2, Board::BOTTOM_F + 3);
						cout << "YOUR SCORE IS : " << score << endl;
						resetGame();
						break;
					}
					if (exitGame) {
						gotoxy(Board::LEFT_F + 2, Board::BOTTOM_F + 5);
						cout << "BYE BYE" << endl;
					}
					break;
				}
			}
		}
	}
}


// Create new Object Game
GameObjects * TetrisGame::createNewObject(int & type,Board board )
{
	GameObjects * res;
	int randObj = rand() % RAND;

	switch (randObj)
	{
	case 0:
		res = new Bomb(board);
		updateStartBoard(B, board);
		type = B;
		break;
	case 1:
		res = new Joker(board);
		updateStartBoard(J, board);
		type = J;
		break;
	case 2:
		res = new Square(board);
		updateStartBoard(SQ, board);
		type = SQ;
		break;
	case 3:
		res = new Line(board);
		updateStartBoard(R, board);
		type = R;

		break;
	case 4:
		res = new Plus(board);
		updateStartBoard(P, board);
		type = P;
		break;
	case 5:
		res = new Zshape(board);
		updateStartBoard(Z, board);
		type = Z;
		break;
	case 6:
		res = new Lshape(board);
		updateStartBoard(L, board);
		type = L;
		break;

	default:
		res = new Line(board);
		updateStartBoard(R, board);
		type = R;
		break;
	}

	res->setSerialNumber(serialNumber);
	return res;
}

// check GAMEOVER
bool TetrisGame::checkGameOver(int typeShape, Board board)
{
	switch (typeShape)
	{
	case B:

		if (!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP)))
			return false;
		break;
	case J:
		if (!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP)))
			return false;
		break;
	case Type::SQ:
		if (!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP)) ||
			(!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP))) ||
			(!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP + 1))) ||
				(!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP + 1))))
				return false;
		break;
	case Type::R:
		for (int i = 0; i < 4; i++)
			if (!(board.isValid((Board::GameZone::LEFT + Board::GameZone::RIGHT) / 2 - 1 + i, Board::GameZone::TOP)))
				return false;
		break;
	case Type::P:
		if ( !(board.isValid(X_SQ - 1, Y_SQ + 1)) || (!(board.isValid(X_SQ, Y_SQ)) ||
			(!(board.isValid(X_SQ, Y_SQ + 1)) || (!(board.isValid(X_SQ + 1, Y_SQ + 1))))))
			return false;
		break;
	case Type::Z:
		if (!(board.isValid(X_SQ, Y_SQ)) || (!(board.isValid(X_SQ + 1, Y_SQ)) ||
			(!(board.isValid(X_SQ + 1, Y_SQ)) || (!(board.isValid(X_SQ + 2, Y_SQ + 1))))))
			return false;
		break;
	case Type::L:
		if (!(board.isValid(X_SQ - 1, Y_SQ)) || (!(board.isValid(X_SQ - 1, Y_SQ + 1)) ||
			(!(board.isValid(X_SQ, Y_SQ + 1)) || (!(board.isValid(X_SQ + 1, Y_SQ + 1))))))
			return false;
		break;
	default:
		break;
	}
	return true;
}

// Update Start Board
void TetrisGame::updateStartBoard(int typeShape, Board board)
{
	switch (typeShape)
	{
	case Type::Single:
		board.turnOnPoint((board.gameZone.left + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP, serialNumber);
	
		break;
	case Type::SQ:
		board.turnOnPoint((board.gameZone.left + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP,serialNumber);
		board.turnOnPoint((board.gameZone.left + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP,serialNumber);
		board.turnOnPoint((board.gameZone.left + Board::GameZone::RIGHT) / 2, Board::GameZone::TOP + 1,serialNumber);
		board.turnOnPoint((board.gameZone.left + Board::GameZone::RIGHT) / 2 + 1, Board::GameZone::TOP + 1,serialNumber);
		break;
	case Type::R:
		for(int i=0; i<4;i++)
			board.turnOnPoint((board.gameZone.left + Board::GameZone::RIGHT) / 2 - 1 + i , Board::GameZone::TOP,serialNumber);
		break;
	case Type::P:
		board.turnOnPoint(X_SQ - 1, Y_SQ + 1, serialNumber);
		board.turnOnPoint(X_SQ, Y_SQ, serialNumber);
		board.turnOnPoint(X_SQ, Y_SQ + 1, serialNumber);
		board.turnOnPoint(X_SQ + 1, Y_SQ + 1, serialNumber);
		break;
	case Type::L:
		board.turnOnPoint(X_SQ - 1, Y_SQ, serialNumber);
		board.turnOnPoint(X_SQ - 1, Y_SQ + 1, serialNumber);
		board.turnOnPoint(X_SQ, Y_SQ + 1, serialNumber);
		board.turnOnPoint(X_SQ + 1, Y_SQ + 1, serialNumber);
		break;
	case Type::Z:
		board.turnOnPoint(X_SQ, Y_SQ, serialNumber);
		board.turnOnPoint(X_SQ + 1, Y_SQ, serialNumber);
		board.turnOnPoint(X_SQ + 1, Y_SQ + 1, serialNumber);
		board.turnOnPoint(X_SQ + 2, Y_SQ + 1, serialNumber);
		break;
	default:
		break;
		
	}
	Sleep(120);
}

//Hide Cursor
void TetrisGame::hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);
}
