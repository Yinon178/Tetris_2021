#pragma once
#include "TopBoard.h"
#include "Point.h"

enum Sign { J = 'O', B = '@' }; // signs on the board of BOMB & JOKER
enum {ROWS = 21, COLS = 12};

class TopBoard;

class GameZone {
public:
	int left, right, top = 5, bottom = 22;
	GameZone(int player) : left(player == 1 ? 10 : 60), right(player == 1 ? 21 : 71) {};
};

class GameFrame {
public:
	int left_f, right_f, top_f, bottom_f;
	GameFrame(GameZone gameZone) { left_f = gameZone.left - 1; right_f = gameZone.right + 1; top_f = gameZone.top - 4; bottom_f = gameZone.bottom + 1; }; // the frame of all the board (include menu)
};

class Board {

	Point boardGame[ROWS][COLS];
	
	int player;

public:
	GameZone gameZone;

	GameFrame gameFrame;

	TopBoard* topB;

	Board(int _player) : player(_player), gameZone(_player), gameFrame(gameZone), topB(new TopBoard(this)) { setBoard(); }; // ctr 

	~Board() { delete topB; }; // dctr

	

	void printFrame();

	void setBoard(bool pause=false);

	void cleanGameOver();

	int getScore();

	bool isFullLine (int curLine, bool & isJokerInLine);

	bool isEmptyLine(int curLine);

	bool cleanLines(int startLine);

	int blowUpSquare(int x, int y);

	bool checkInGameZone(int x, int y)
	{
		return (x >= gameZone.left && x <= gameZone.right && y >= gameZone.top && y <= gameZone.bottom);
	}

	char getSign(int x, int y)
	{
		return boardGame[y - gameZone.top + 3][x - gameZone.left].getSign();
	}

	int getSerial(int x, int y)
	{
		return (boardGame[y - gameZone.top + 3][x - gameZone.left].getSerialNumber());
	}

	bool isValid(int x, int y)
	{
		return (!(boardGame[y - gameZone.top + 3][x - gameZone.left].isBusy()) &&
			(x >= gameZone.left && x <= gameZone.right && y >= gameZone.top && y <= gameZone.bottom) && (boardGame[y - gameZone.top + 3][x - gameZone.left].getSerialNumber() != -2));
	}

	void turnOnPoint(int x, int y,int serial=0, char ch = '#')
	{
		boardGame[y - gameZone.top + 3][x - gameZone.left].setPoint(x, y, true,serial,ch);
		boardGame[y - gameZone.top + 3][x - gameZone.left].draw(ch);
	}
	void turnOffPoint(int x, int y)
	{
		if (x >= gameZone.left && x <= gameZone.right && y >= gameZone.top && y <= gameZone.bottom) {
			boardGame[y - gameZone.top + 3][x - gameZone.left].setPoint(x, y, false);
			boardGame[y - gameZone.top + 3][x - gameZone.left].draw(' ');
		}
	}

	bool updateBoard();

	void printShapes();

	void updateScoreBoard(int addScore);

	void updateNumOfShapesBoard();

	// get serial Number and build the shape from the start
	Point * createSerialShape(int serial, int row, int & shapeSize, Point * res);

	void moveShape(Point * arr, int size);

	void hardDownShape(Point * arr, int size);

	void updateRecord(int newRecord)
	{
		gotoxy(gameFrame.right_f + 5, (gameFrame.bottom_f + gameFrame.top_f) / 2 - 3);
		cout << newRecord;
	}

	void printMenu(bool pause = false);
};
