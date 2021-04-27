#pragma once
#include "gotoxy.h"
#include <iostream>
#include <Windows.h>

class Point
{
	//Data members
	int x = 0;
	int y = 0;
	bool busy = false;
	char ch = 0;
	int serialNumber = 0;

public:
	
	//ctor 
	Point(int _x, int _y, bool _busy = false, char _ch = '#', int _serialNumber = 0) : x(_x), y(_y), busy(_busy), ch(_ch), serialNumber(_serialNumber) {};

	Point() {};

	void setPoint(int _x, int _y, bool _busy = false, int _serialNumber = 0, char _ch = '#') { x = _x; y = _y; busy = _busy; serialNumber = _serialNumber; ch = _ch; }

	void setSerialNumber(int _serialNumber) { serialNumber = _serialNumber; }

	 char getSign() const{ return ch; };

	 //draw
	 void draw(char ch = '#', bool colored=true) const;

	// get data members of the class
	int getx() const 	{ return x; }

	int gety() const	{ return y; }
	
	bool isBusy() const { return busy; }

	int getSerialNumber()const { return serialNumber; }

	
};