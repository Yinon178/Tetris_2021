#include "TopBoard.h"
#include <Windows.h>

void TopBoard::printTopBoard()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 15);
	gotoxy(board.gameFrame.left_f + 1, board.gameFrame.top_f + 1);
	cout << "          " << endl;
	gotoxy(board.gameFrame.left_f + 1, board.gameFrame.top_f + 1);
	cout << "Shapes:" << numOfShapes << endl;
	gotoxy(board.gameFrame.left_f + 1, board.gameFrame.top_f + 2);
	for (int i = 0; i < 10; i++)
		cout << " ";
	cout << endl;
	gotoxy(board.gameFrame.left_f + 1, board.gameFrame.top_f + 2);
	cout << "       " << endl;
	gotoxy(board.gameFrame.left_f + 1, board.gameFrame.top_f + 2);
	cout << "S:" << score << endl;
	gotoxy(board.gameFrame.left_f + 1, board.gameFrame.top_f + 3);
	for (int i = 0; i < 10; i++)
		cout << "_";
	cout << endl;

}
