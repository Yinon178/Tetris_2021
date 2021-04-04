#pragma once
#include "Board.h"
#include "GameObjects.h"
#include "Point.h"
#include <Windows.h>
#include <conio.h>

class TetrisGame {
	
	Board boardGamePlayer1, boardGamePlayer2;
public:

	void resetGame(){
		boardGamePlayer1.setBoard(1);
		boardGamePlayer2.setBoard(2);
	}
	// <<<RUN>>>
	void run();

	bool checkGameOver(int typeShapea);

	void updateStartBoard(int typeShape, Board board);


	void hideCursor();


	GameObjects * createNewObject(int & type, Board board);

};
