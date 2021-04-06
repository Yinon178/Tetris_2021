#pragma once
#include "Board.h"
#include "GameObjects.h"
#include "Point.h"
#include <Windows.h>
#include <conio.h>

class TetrisGame {

	Board boardGamePlayer1, boardGamePlayer2;
public:
	TetrisGame() : boardGamePlayer1(Board(1)), boardGamePlayer2(Board(2)) {};

	void resetGame(){
		boardGamePlayer1.setBoard();
		boardGamePlayer2.setBoard();
	}
	// <<<RUN>>>
	void run();

	bool checkGameOver(int typeShapea, Board &board);

	void updateStartBoard(int typeShape, Board &board);


	void hideCursor();


	GameObjects * createNewObject(int & type, Board &board);

};
