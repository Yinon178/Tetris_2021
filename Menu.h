#pragma once
#include "gotoxy.h"

enum MenuKeys { START = '1', STARTNOCOLOR = '5', PAUSE = '\x1b', RESUME = '2',
	FAST_SPEED = '3', NORMAL_SPEED = '4', EXIT = '9', INSTRUCTIONS ='8'};

class Menu
{
	bool pause = false;
	bool gameRunning = false;
	int startX, startY;
	void clearMenu();


public:
	Menu() = delete; // del defualt ctr

	Menu(int x, int y) : startX(x), startY(y) { printMenu(); };

	void printMenu();

	void gameStarted();

	void gameFinished();

	bool isPaused();

	void pauseGame();

	void resumeGame();

	void printInstructions();

};


