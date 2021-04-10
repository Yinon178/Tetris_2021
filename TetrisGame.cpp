#include "TetrisGame.h"
#include "Board.h"
#include "Line.h"
#include "Square.h"
#include "Bomb.h"
#include "Plus.h"
#include "Zshape.h"
#include "Lshape.h"
#include "MirrorLshape.h"
#include "MirrorZshape.h"


enum {RAND = 7};

enum Type{Single, SQ, R, P, L, Z, MZ, ML};

enum Speed {Fast = 130, Normal = 200 };

int static serialNumber = 1;


//<<<RUN>>>
void TetrisGame::run() {

	GameObjects *objectPlayer1, *objectPlayer2;
	int gameSpeed = Normal;
	char keyPressed = 0, keyPressedPlayer1 = DEFAULT, keyPressedPlayer2 = DEFAULT;
	int typePlayer1 = -1, typePlayer2 = -1;
	bool gameOver = false, exitGame = false;


	while (keyPressed != EXIT && !exitGame)
	{
		hideCursor();
		gameSpeed = Speed::Normal;
		if (_kbhit()) // checks if there is anything in the buffer
		{
			keyPressed = _getch();
			if (keyPressed == INSTRUCTIONS) 
			{
				mainMenu.printInstructions();
				while (true)
				{
					Sleep(100);
					if (_kbhit()) {

						parseKeysPressed(keyPressed, keyPressedPlayer1, keyPressedPlayer2);
						if (keyPressed == EXIT)
						{
							keyPressed = 0;
							mainMenu.printMenu();
							break;
						}
					}
				}
			}
			if (keyPressed == START || keyPressed == STARTNOCOLOR)
			{
				setColored(keyPressed == START);
				mainMenu.gameStarted();

				if (gameOver) {
					gameOver = false;
					boardGamePlayer1.cleanGameOver();
                    boardGamePlayer2.cleanGameOver();
				}
				if (exitGame)
					break;
				objectPlayer1 = createNewObject(typePlayer1, boardGamePlayer1);
				objectPlayer2 = createNewObject(typePlayer2, boardGamePlayer2);
				while (true)
				{

						while (!gameOver && !exitGame)
						{
							if (!(objectPlayer1->move(keyPressedPlayer1)))
							{
								if (!checkGameOver(typePlayer1, boardGamePlayer1))
								{
									gameOver = true;
									break;
								}
								delete objectPlayer1;
								objectPlayer1 = createNewObject(typePlayer1, boardGamePlayer1);
							}
							if (!(objectPlayer2->move(keyPressedPlayer2)))
							{
								if (!checkGameOver(typePlayer2, boardGamePlayer2))
								{
									gameOver = true;
									break;
								}
								delete objectPlayer2;
								objectPlayer2 = createNewObject(typePlayer2, boardGamePlayer2);
							}
							keyPressed = 0;
							keyPressedPlayer1 = DEFAULT; // take the head of the buffer
							keyPressedPlayer2 = DEFAULT;
							Sleep(gameSpeed);
							if (_kbhit()) // checks if there is anything in the buffer
							{
								parseKeysPressed(keyPressed, keyPressedPlayer1, keyPressedPlayer2);
								if (keyPressed == EXIT) {
									exitGame = true;
									break;
								}
								else if (keyPressed == NORMAL_SPEED)
									gameSpeed = Speed::Normal;
								else if (keyPressed == FAST_SPEED)
									gameSpeed = Speed::Fast;

								else if (keyPressed == PAUSE)
								{
									mainMenu.pauseGame();
									while (true)
									{
										if (_kbhit()) {

											parseKeysPressed(keyPressed, keyPressedPlayer1, keyPressedPlayer2);
											if (keyPressed == EXIT)
											{
												gameOver = true;
												break;
											}
												
											else if (keyPressed == RESUME) {
												boardGamePlayer1.setBoard(true);
												boardGamePlayer2.setBoard(true);
												mainMenu.resumeGame();
												break;
											}
												
										}
										Sleep(gameSpeed);
									}
								}
							}


						}
					if (gameOver)
					{
						annonceWinner(typePlayer1, typePlayer2);
						resetGame();
						mainMenu.gameFinished();
						break;
					}
					if (exitGame) {
						gotoxy((boardGamePlayer1.gameFrame.right_f + boardGamePlayer2.gameFrame.left_f) / 2 - 5, boardGamePlayer1.gameFrame.bottom_f);
						cout << "BYE BYE" << endl;
					}
					break;
				}
			}
		}
	}
}


// Create new Object Game
GameObjects * TetrisGame::createNewObject(int & type,Board &board )
{
	GameObjects * res=NULL;
	
	if (rand() % 20 == 1) {
		res = new Bomb(board);
		updateStartBoard(B, board);
		type = B;
	}
	else
	{
		int randObj = rand() % RAND;

		switch (randObj)
		{
		case 0:
			res = new Square(board);
			updateStartBoard(SQ, board);
			type = SQ;
			break;
		case 1:
			res = new Line(board);
			updateStartBoard(R, board);
			type = R;

			break;
		case 2:
			res = new Plus(board);
			updateStartBoard(P, board);
			type = P;
			break;
		case 3:
			res = new Zshape(board);
			updateStartBoard(Z, board);
			type = Z;
			break;
		case 4:
			res = new Lshape(board);
			updateStartBoard(L, board);
			type = L;
			break;
		case 5:
			res = new MirrorZshape(board);
			updateStartBoard(MZ, board);
			type = MZ;
			break;
		case 6:
			res = new MirrorLshape(board);
			updateStartBoard(ML, board);
			type = ML;
			break;
		}
	}

	res->setSerialNumber(serialNumber);
	serialNumber++;
	return res;
}

// check GAMEOVER
bool TetrisGame::checkGameOver(int typeShape, Board &board)
{
	switch (typeShape)
	{
	case B:

		if (!(board.isValid((board.gameZone.left + board.gameZone.right) / 2, board.gameZone.top)))
			return false;
		break;
	case Type::SQ:
		if (!(board.isValid((board.gameZone.left + board.gameZone.right) / 2, board.gameZone.top)) ||
			(!(board.isValid((board.gameZone.left + board.gameZone.right) / 2 + 1, board.gameZone.top))) ||
			(!(board.isValid((board.gameZone.left + board.gameZone.right) / 2, board.gameZone.top + 1))) ||
				(!(board.isValid((board.gameZone.left + board.gameZone.right) / 2 + 1, board.gameZone.top + 1))))
				return false;
		break;
	case Type::R:
		for (int i = 0; i < 4; i++)
			if (!(board.isValid((board.gameZone.left + board.gameZone.right) / 2 - 1 + i, board.gameZone.top)))
				return false;
		break;
	case Type::P:
		if ( !(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1)) || (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1)) || (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1))))))
			return false;
		break;
	case Type::Z:
		if (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top)) || (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top)) || (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 2, board.gameZone.top + 1))))))
			return false;
		break;
	case Type::L:
		if (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top)) || (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1)) || (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1))))))
			return false;
		break;
	case Type::MZ:
		if (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1)) || 
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top))))))
			return false;
		break;
	case Type::ML:
		if (!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1)) ||
			(!(board.isValid(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top))))))
			return false;
		break;
	default:
		break;
	}
	return true;
}

// Update Start Board
void TetrisGame::updateStartBoard(int typeShape, Board &board)
{
	switch (typeShape)
	{
	case Type::Single:
		board.turnOnPoint((board.gameZone.left + board.gameZone.right) / 2, board.gameZone.top, serialNumber);
	
		break;
	case Type::SQ:
		board.turnOnPoint((board.gameZone.left + board.gameZone.right) / 2, board.gameZone.top,serialNumber);
		board.turnOnPoint((board.gameZone.left + board.gameZone.right) / 2 + 1, board.gameZone.top,serialNumber);
		board.turnOnPoint((board.gameZone.left + board.gameZone.right) / 2, board.gameZone.top + 1,serialNumber);
		board.turnOnPoint((board.gameZone.left + board.gameZone.right) / 2 + 1, board.gameZone.top + 1,serialNumber);
		break;
	case Type::R:
		for(int i=0; i<4;i++)
			board.turnOnPoint((board.gameZone.left + board.gameZone.right) / 2 - 1 + i , board.gameZone.top,serialNumber);
		break;
	case Type::P:
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1, serialNumber);
		break;
	case Type::L:
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1, serialNumber);
		break;
	case Type::Z:
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 2, board.gameZone.top + 1, serialNumber);
		break;
	case Type::MZ:
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top, serialNumber);
		break;
	case Type::ML:
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) - 1, board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2), board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top + 1, serialNumber);
		board.turnOnPoint(((board.gameZone.left + board.gameZone.right) / 2) + 1, board.gameZone.top, serialNumber);
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

void TetrisGame::parseKeysPressed(char &keyPressed, char &keyPressedPlayer1, char &keyPressedPlayer2)
{
	char res;
	std::string player1Keys = "adswx", player2Keys = "jlkim", menuKeys = "1289534\x1b";
	while (_kbhit()) {
		res = std::tolower(_getch());
		if (player1Keys.find(res) != std::string::npos)
		{
			keyPressedPlayer1 = res;
		}
		if (menuKeys.find(res) != std::string::npos)
		{
			keyPressed = res;
		}
		else if (player2Keys.find(res) != std::string::npos)
		{
			switch (res)
			{
			case 'j':
				keyPressedPlayer2 = LEFT;
				break;
			case 'l':
				keyPressedPlayer2 = RIGHT;
				break;
			case 'k':
				keyPressedPlayer2 = ROUTE;
				break;
			case 'i':
				keyPressedPlayer2 = ROUTEC;
				break;
			case 'm':
				keyPressedPlayer2 = HARD_DOWN;
				break;
			default:
				cout << "ERORR in parsing player 2 keys";
				exit(-1);
				break;
			}
		}	

	}
	purgeKeyboardBuffer();
}

void TetrisGame::purgeKeyboardBuffer() 
{
	while (_kbhit()) {
		_getch();
	}

}

void TetrisGame::annonceWinner(int typePlayer1, int typePlayer2)
{
	bool player1win = true, player2win = true;
	int xPrintLoc = (boardGamePlayer1.gameFrame.right_f + boardGamePlayer2.gameFrame.left_f) / 2 - 10;
	int yPrintLoc = boardGamePlayer2.gameFrame.bottom_f;
	player1win = checkGameOver(typePlayer1, boardGamePlayer1);
	player2win = checkGameOver(typePlayer2, boardGamePlayer2);
	gotoxy(xPrintLoc, yPrintLoc);
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 7);
	if (!player1win && !player2win)
	{
		if (boardGamePlayer1.getScore() == boardGamePlayer2.getScore())
		{
			cout << "~~TIE~~";
		
		}
		else if (boardGamePlayer1.getScore() > boardGamePlayer2.getScore()) 
		{
			cout << "~~PLAYER ONE WINS~~";
		}
		else 
		{
			cout << "~~PLAYER TWO WINS~~";
		}
	
	}
	else if (!player1win)
	{
		cout << "~~PLAYER TWO WINS~~";
	}
	else 
	{
		cout << "~~PLAYER ONE WINS~~";
	}

}
