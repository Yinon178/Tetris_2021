#include "Point.h"



void Point::draw(char ch,bool colored) const
{
	int colorShape = 7;
	if (colored) {
		colorShape = getSerialNumber() % 7 + 1;
	}
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, colorShape);
	gotoxy(x, y);
	std::cout << ch << std::endl;
}
