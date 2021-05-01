#pragma once
#include "Shape.h"
#include "board.h"

class AI
{
	double heightWeight;
   
	double linesWeight;
   
	double holesWeight;
   
	double bumpinessWeight;


public:
	AI(double _heightWeight, double _linesWeight, double _holesWeight, double _bumpinessWeight) : heightWeight(_heightWeight),
		linesWeight(_linesWeight), holesWeight(_holesWeight), bumpinessWeight(_bumpinessWeight) {};

	auto best(Board board, Shape shape)
};

