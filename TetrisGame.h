#pragma once
#include "Board.h"
#include "GameObjects.h"
#include "Point.h"
#include "Menu.h"
#include <Windows.h>
#include <conio.h>


class TetrisGame {

	Board boardGamePlayer1, boardGamePlayer2;
	Menu mainMenu;
public:
	TetrisGame() : boardGamePlayer1(Board(1)),
		boardGamePlayer2(Board(2)),
		mainMenu(Menu(boardGamePlayer1.gameFrame.right_f + 5, (boardGamePlayer1.gameFrame.bottom_f + boardGamePlayer1.gameFrame.top_f) / 2)) {};

	void resetGame(){
		gotoxy((boardGamePlayer1.gameFrame.right_f + boardGamePlayer2.gameFrame.left_f) / 2 - 10, boardGamePlayer1.gameFrame.top_f);
		std::cout << "                           " << std::endl;
		boardGamePlayer1.setBoard();
		boardGamePlayer2.setBoard();
	}
	// <<<RUN>>>
	void run();

	void setColored(bool colored)
	{
		boardGamePlayer1.setColored(colored);
		boardGamePlayer2.setColored(colored);
	}

	bool checkGameOver(int typeShapea, Board &board);

	void updateStartBoard(int typeShape, Board &board);


	void hideCursor();

	void purgeKeyboardBuffer();

	void annonceWinner (int typePlayer1, int typePlayer2);


	GameObjects * createNewObject(int & type, Board &board);

};
