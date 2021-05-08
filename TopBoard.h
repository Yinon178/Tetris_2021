#pragma once
#include "Point.h"

class Board;

enum SCORE{SOFT_DROP = 1, HARD_DROP = 2, SINGLE_LINE= 100, DOUBLE_LINE = 300, TRIPLE_LINE = 500, BOMB_EXPLODE = -50};

//class TopBoardInterface {
//
//public:
//
//	virtual void resetTopBoard() = 0;
//
//	virtual int getScore() = 0;
//
//	virtual void updateScore(int addScore) = 0;
//
//	virtual void printTopBoard() = 0;
//
//	virtual void updateNumOfShapes() = 0;
//
//};
//
//class TopBoardDummy {
//
//public:
//
//	void resetTopBoard() { return; };
//
//	int getScore() { return 0; };
//
//	void updateScore(int addScore) { return; }
//
//	void printTopBoard() { return; }
//
//	void updateNumOfShapes() { return; }
//
//};

class TopBoard {
	 //Data members
	int numOfShapes;
	int score;
	bool dummy = false;

public:
	Board *board;

	TopBoard(Board* _board) : numOfShapes(0), score(0), board(_board) {};

	TopBoard(Board* _board, bool _dummy) : numOfShapes(0), score(0), board(_board), dummy(_dummy) {};

	void resetTopBoard() {
		numOfShapes = 0; score = 0; printTopBoard();
	}

	int getScore() { return score; }


	void updateScore(int addScore) {
		if (dummy)
			return;
		score += addScore;
		printTopBoard();
	}

	void printTopBoard();



	void updateNumOfShapes() {
		if (!dummy)
			numOfShapes++;
	}

	void enableDummy() { dummy = true; }

	void disableDummy() { dummy = false; }

};

