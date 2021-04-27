#pragma once
#include <iostream>

enum eKEYS { LEFT = 'a', RIGHT = 'd', HARD_DOWN = 'x', ROUTE = 's', ROUTEC = 'w', JSTOP = 's', DEFAULT = ' ', ESC = 27 };

void gotoxy(int x, int y);

void ClearScreen();
