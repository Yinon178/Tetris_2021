#pragma once
#include "Board.h"
#include "GameObjects.h"
#include "Point.h"
#include "Menu.h"
#include "AI.h"
#include <Windows.h>
#include <conio.h>



class TetrisGame {
    
	Board boardGamePlayer1, boardGamePlayer2;
	Menu mainMenu;
    AI AIPlayer1, AIPlayer2;

public:
    bool isPlayer1AI = false;
    bool isPlayer2AI = false;
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

	void gameHandeling(char& keyPressed, bool& gameOver, bool& exitGame, GameObjects*& objectPlayer1, int& typePlayer1, GameObjects*& objectPlayer2, int& typePlayer2, char& keyPressedPlayer1, char& keyPressedPlayer2, int& gameSpeed, int& retflag);

	void userGameInputHandeling(bool& gameOver, bool& exitGame, GameObjects*& objectPlayer1, char& keyPressedPlayer1, int& typePlayer1, GameObjects*& objectPlayer2, char& keyPressedPlayer2, int& typePlayer2, char& keyPressed, int& gameSpeed);

	void setColored(bool colored)
	{
		boardGamePlayer1.setColored(colored);
		boardGamePlayer2.setColored(colored);
	}

	bool checkGameOver(int typeShapea, Board &board);

	void updateStartBoard(int typeShape, Board &board);

	void instructionsHandeling(char keyPressed, char keyPressedPlayer1, char keyPressedPlayer2);

	void hideCursor();

	void purgeKeyboardBuffer();

	void annonceWinner (int typePlayer1, int typePlayer2);

	GameObjects * createNewObject(int & type, Board &board);

};