#pragma once
#include "TopBoard.h"
#include "Point.h"
#include "GameObjects.h"

enum Sign {B = '@' }; // signs on the board of BOMB
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
	bool colored = true;

public:
	GameZone gameZone;

	GameFrame gameFrame;

	TopBoard* topB;

	Board() : player(1), gameZone(player), gameFrame(gameZone), topB(nullptr) {};

	Board(int _player) : player(_player), gameZone(_player),
    gameFrame(gameZone), topB(new TopBoard(this)) { setBoard(); }; // ctr

	Board(const Board& b) : player(b.getPlayer()), gameZone(b.getPlayer()),
		gameFrame(gameZone), topB(new TopBoard(this)) { copygrid(b); }; // copy ctr

	~Board() { delete topB; }; // dctr

	friend void swap(Board& first, Board& second) // nothrow
	{
		using std::swap;
		swap(first.player, second.player);
		swap(first.colored, second.colored);
		swap(first.boardGame, second.boardGame);
		swap(first.gameZone, second.gameZone);
		swap(first.gameFrame, second.gameFrame);
		swap(first.topB, second.topB);

	}
	Board& operator=(Board other)
	{
		swap(*this, other);

		return *this;
	}

	Board(Board&& other) noexcept
		: Board() // initialize via default constructor, C++11 only
	{
		swap(*this, other);
	}

	void setColored(bool _colored)
	{
		colored = _colored;
	}

	void printFrame() const;

	void setBoard(bool pause = false);

	void copygrid(const Board& b);

	void cleanGameOver();

	int getScore() const;

	bool isFullLine (int curLine, bool cleanIfFound = true);
    
    void cleanLine(int curLine);

	bool isEmptyLine(int curLine) const;

	bool cleanLines(int startLine, bool mark = true);

	int blowUpSquare(int x, int y);

	bool checkInGameZone(int x, int y) const
	{
		return (x >= gameZone.left && x <= gameZone.right && y >= gameZone.top && y <= gameZone.bottom);
	}

	bool isPointInBoardGameBusy(int x, int y) const
	{
		return boardGame[x][y].isBusy();
	}

	char getSign(int x, int y) const
	{
		return boardGame[y - gameZone.top + 3][x - gameZone.left].getSign();
	}
    
    char getPlayer() const
    {
        return player;
    }

	int getSerial(int x, int y) const
	{
		return (boardGame[y - gameZone.top + 3][x - gameZone.left].getSerialNumber());
	}

	bool isValid(int x, int y) const
	{
		return (!(boardGame[y - gameZone.top + 3][x - gameZone.left].isBusy()) &&
			(x >= gameZone.left && x <= gameZone.right && y >= gameZone.top && y <= gameZone.bottom) && (boardGame[y - gameZone.top + 3][x - gameZone.left].getSerialNumber() != -2));
	}

	void turnOnPoint(int x, int y, int serial=0, char ch = '#', bool mark = true)
	{
		boardGame[y - gameZone.top + 3][x - gameZone.left].setPoint(x, y, true, serial,ch);
		if (mark)
			boardGame[y - gameZone.top + 3][x - gameZone.left].draw(ch, colored);
	}
	void turnOffPoint(int x, int y,bool mark=true)
	{
		if (x >= gameZone.left && x <= gameZone.right && y >= gameZone.top && y <= gameZone.bottom) {
			boardGame[y - gameZone.top + 3][x - gameZone.left].setPoint(x, y, false);
			if (mark)
				boardGame[y - gameZone.top + 3][x - gameZone.left].draw(' ', colored);
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
		std::cout << newRecord;
	}
    
    int aggregateHeight();
    
	int columnHeight(int column);
    
	int lines();
    
	int holes();
    
	int bumpiness();

};
