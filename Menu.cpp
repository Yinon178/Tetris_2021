#include "Menu.h"
#include <Windows.h>

void Menu::printMenu()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 7);
	clearMenu();
	if (!gameRunning)
	{
		gotoxy(startX, startY);
		cout << "(" << START - '0' << ") to START" << endl;
		gotoxy(startX, startY + 1);
		cout << "(" << STARTNOCOLOR - '0' << ") to START without colors" << endl;
		gotoxy(startX, startY + 2);
		cout << "(" << INSTRUCTIONS - '0' << ") Present keys" << endl;

	}
	if (!pause && gameRunning)
	{
		gotoxy(startX, startY + 1);
		cout << "(" << FAST_SPEED - '0' << ") to FAST SPEED" << endl;
		gotoxy(startX, startY + 2);
		cout << "(" << NORMAL_SPEED - '0' << ") to NORMAL SPEED" << endl;
		gotoxy(startX, startY);
		cout << "(" << "esc" << ") to PAUSE" << endl;
	}
	else if (pause)
	{
		gotoxy(startX, startY);
		cout << "(" << RESUME - '0' << ") to RESUME" << endl;
	}

	gotoxy(startX, startY + 3);
	cout << "(" << EXIT - '0' << ") to EXIT" << endl;
}

void Menu::gameStarted()
{
	gameRunning = true;
	printMenu();
}

void Menu::gameFinished()
{
	gameRunning = false;
	pause = false;
	printMenu();
}

bool Menu::isPaused()
{
	return pause;
}

void Menu::pauseGame()
{
	pause = true;
	printMenu();
}

void Menu::resumeGame()
{
	pause = false;
	printMenu();
}

void Menu::clearMenu()
{
	for (int i = 0; i < 14; i++)
	{
		gotoxy(startX, startY + i);
		cout << "                               " << endl;
	}

}

void Menu::printInstructions()
{
	clearMenu();
	gotoxy(startX, startY);
	cout << "(" << EXIT - '0' << ") to Exit Instructions" << endl;
	gotoxy(startX, startY + 1);
	cout << "Left Player /  Right Player" << endl;
	gotoxy(startX, startY + 2);
	cout << "```a / j``` - left" << endl;
	gotoxy(startX, startY + 3);
	cout << "```d / l``` - right" << endl;
	gotoxy(startX, startY + 4);
	cout << "```s / k``` - rotate CW" << endl;
	gotoxy(startX, startY + 5);
	cout << "```w / i``` - rotate CCW" << endl;
	gotoxy(startX, startY + 6);
	cout << "```x / m``` - hard drop (SHAPES)" << endl;
}
