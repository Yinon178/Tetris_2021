#include "TopBoard.h"
#include <Windows.h>
#include "board.h"

void TopBoard::printTopBoard()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 7);
	gotoxy(board->gameFrame.left_f + 1, board->gameFrame.top_f + 1);
	std::cout << "          " << std::endl;
	gotoxy(board->gameFrame.left_f + 1, board->gameFrame.top_f + 1);
	std::cout << "Shapes:" << numOfShapes << std::endl;
	gotoxy(board->gameFrame.left_f + 1, board->gameFrame.top_f + 2);
	for (int i = 0; i < 10; i++)
		std::cout << " ";
	std::cout << std::endl;
	gotoxy(board->gameFrame.left_f + 1, board->gameFrame.top_f + 2);
	std::cout << "       " << std::endl;
	gotoxy(board->gameFrame.left_f + 1, board->gameFrame.top_f + 2);
	std::cout << "S:" << score << std::endl;
	gotoxy(board->gameFrame.left_f + 1, board->gameFrame.top_f + 3);
	for (int i = 0; i < 10; i++)
		std::cout << "_";
	std::cout << std::endl;

}
