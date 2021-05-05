#include "Menu.h"
#include <Windows.h>
#include <conio.h>
#include <queue>



void Menu::playersPickingMenu(bool& AI1, bool& AI2)
{
    char keyPressed = 0;
    gotoxy(startX, startY);
    std::cout << "(" << PLAYERVSPLAYER - '0' << ") to PLAYERVSPLAYER" << std::endl;
    gotoxy(startX, startY + 1);
    std::cout << "(" << AIVSPLAYER - '0' << ") to AIVSPLAYER" << std::endl;
    gotoxy(startX, startY + 2);
    std::cout << "(" << AIVSAI - '0' << ") AIVSAI" << std::endl;
    
    while (true) {
        if (_kbhit()) // checks if there is anything in the buffer
        {
            keyPressed = _getch();
            if (keyPressed == PLAYERVSPLAYER || keyPressed == AIVSPLAYER ||keyPressed == AIVSAI) {
                if (keyPressed == AIVSPLAYER)
                {
                    AI1 = true;
                }
                else if (keyPressed == AIVSAI)
                {
                    AI1 = true;
                    AI2 = true;
                }
                return;
            }
        }
        Sleep(100);
    }
}

void Menu::printMenu()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 7);
	clearMenu();
	if (!gameRunning)
	{
		gotoxy(startX, startY);
		std::cout << "(" << START - '0' << ") to START" << std::endl;
		gotoxy(startX, startY + 1);
		std::cout << "(" << STARTNOCOLOR - '0' << ") to START without colors" << std::endl;
		gotoxy(startX, startY + 2);
		std::cout << "(" << INSTRUCTIONS - '0' << ") Present keys" << std::endl;

	}
	if (!pause && gameRunning)
	{
		gotoxy(startX, startY + 1);
		std::cout << "(" << FAST_SPEED - '0' << ") to FAST SPEED" << std::endl;
		gotoxy(startX, startY + 2);
		std::cout << "(" << NORMAL_SPEED - '0' << ") to NORMAL SPEED" << std::endl;
		gotoxy(startX, startY);
		std::cout << "(" << "esc" << ") to PAUSE" << std::endl;
	}
	else if (pause)
	{
		gotoxy(startX, startY);
		std::cout << "(" << RESUME - '0' << ") to RESUME" << std::endl;
	}

	gotoxy(startX, startY + 3);
	std::cout << "(" << EXIT - '0' << ") to EXIT" << std::endl;
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

bool Menu::isPaused() const
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

void Menu::clearMenu() const
{
	for (int i = 0; i < 14; i++)
	{
		gotoxy(startX, startY + i);
		std::cout << "                                " << std::endl;
	}

}

void Menu::printInstructions() const
{
	clearMenu();
	gotoxy(startX, startY);
	std::cout << "(" << EXIT - '0' << ") to Exit Instructions" << std::endl;
	gotoxy(startX, startY + 1);
	std::cout << "Left Player /  Right Player" << std::endl;
	gotoxy(startX, startY + 2);
	std::cout << "```a / j``` - left" << std::endl;
	gotoxy(startX, startY + 3);
	std::cout << "```d / l``` - right" << std::endl;
	gotoxy(startX, startY + 4);
	std::cout << "```s / k``` - rotate CW" << std::endl;
	gotoxy(startX, startY + 5);
	std::cout << "```w / i``` - rotate CCW" << std::endl;
	gotoxy(startX, startY + 6);
	std::cout << "```x / m``` - hard drop (SHAPES)" << std::endl;
}


void Menu::parseKeysPressed(char& keyPressed, char& keyPressedPlayer1, char& keyPressedPlayer2)
{
	char res;
	while (_kbhit()) {
		res = std::tolower(_getch());
		if (player1Keys.find(res) != std::string::npos)
		{
			keyPressedPlayer1 = res;
		}
		if (menuKeys.find(res) != std::string::npos)
		{
			keyPressed = res;
		}
		else if (player2Keys.find(res) != std::string::npos)
		{
			switch (res)
			{
			case 'j':
				keyPressedPlayer2 = LEFT;
				break;
			case 'l':
				keyPressedPlayer2 = RIGHT;
				break;
			case 'k':
				keyPressedPlayer2 = ROUTE;
				break;
			case 'i':
				keyPressedPlayer2 = ROUTEC;
				break;
			case 'm':
				keyPressedPlayer2 = HARD_DOWN;
				break;
			default:
				std::cout << "ERORR in parsing player 2 keys";
				break;
			}
		}

	}
}

void Menu::parseKeysPressed(char& keyPressed, char& keyPressedPlayer1,
                            char& keyPressedPlayer2, AI &AIPlayer1)
{
    char res;
    while (_kbhit()) {
        res = std::tolower(_getch());
        if (!AIPlayer1.bestMovesQueue.empty())
        {
            keyPressedPlayer1 = AIPlayer1.bestMovesQueue.front();
			AIPlayer1.bestMovesQueue.pop();
        }
        if (menuKeys.find(res) != std::string::npos)
        {
            keyPressed = res;
        }
        else if (player2Keys.find(res) != std::string::npos)
        {
            switch (res)
            {
            case 'j':
                keyPressedPlayer2 = LEFT;
                break;
            case 'l':
                keyPressedPlayer2 = RIGHT;
                break;
            case 'k':
                keyPressedPlayer2 = ROUTE;
                break;
            case 'i':
                keyPressedPlayer2 = ROUTEC;
                break;
            case 'm':
                keyPressedPlayer2 = HARD_DOWN;
                break;
            default:
                std::cout << "ERORR in parsing player 2 keys";
                break;
            }
        }

    }
}

void Menu::parseKeysPressed(char& keyPressed, char& keyPressedPlayer1,
    char& keyPressedPlayer2, AI &AIPlayer1, AI &AIPlayer2)
{
    char res;
    while (_kbhit()) {
        res = std::tolower(_getch());
        if (!AIPlayer1.bestMovesQueue.empty())
        {
            keyPressedPlayer1 = AIPlayer1.bestMovesQueue.front();
			AIPlayer1.bestMovesQueue.pop();
        }
        if (menuKeys.find(res) != std::string::npos)
        {
            keyPressed = res;
        }
		if (!AIPlayer2.bestMovesQueue.empty())
		{
			keyPressedPlayer2 = AIPlayer2.bestMovesQueue.front();
			AIPlayer2.bestMovesQueue.pop();
		}

    }
}