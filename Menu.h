#pragma once
#include "gotoxy.h"
#include "AI.h"

enum MenuKeys { START = '1', STARTNOCOLOR = '5', PAUSE = '\x1b', RESUME = '2',
	FAST_SPEED = '3', NORMAL_SPEED = '4', EXIT = '9', INSTRUCTIONS ='8', PLAYERVSPLAYER = '1', AIVSPLAYER = '2', AIVSAI = '3'};

class Menu
{
	inline static const std::string_view player1Keys= "adswx";
	inline static const std::string_view player2Keys = "jlkim";
	inline static const std::string_view menuKeys = "1289534\x1b";
	bool pause = false;
	bool gameRunning = false;
	int startX, startY;
    bool player1AI = false, player2AI = false;
	void clearMenu() const;


public:

	Menu(int x, int y) : startX(x), startY(y) {};

    void playersPickingMenu(bool& AI1, bool& AI2);
    
    bool isPlayer1AI() const {return player1AI;};
    
    bool isPlayer2AI() const {return player2AI;};
    
    void printMenu();

	void gameStarted();

	void gameFinished();

	bool isPaused() const;

	void pauseGame();

	void resumeGame();

	void printInstructions() const;

	void parseKeysPressed(char& keyPressed, char& keyPressedPlayer1, char& keyPressedPlayer2);
    
    void parseKeysPressed(char& keyPressed, char& keyPressedPlayer1, char& keyPressedPlayer2,
                          AI &AIPlayer1);
    
    void parseKeysPressed(char& keyPressed, char& keyPressedPlayer1, char& keyPressedPlayer2,
                          AI &AIPlayer1, AI &AIPlayer2);
    

};


