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

	void parseKeysPressed(char &keyPressed, char &keyPressedPlayer1, char &keyPressedPlayer2);

	void purgeKeyboardBuffer();

	void annonceWinner (int typePlayer1, int typePlayer2);


	GameObjects * createNewObject(int & type, Board &board);

};
