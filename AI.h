#pragma once
#include "board.h"
#include "GameObjects.h"

#include <memory>
#include <queue>

class AI
{
    double heightWeight = 0.510066;

    double linesWeight = 0.760666;

    double holesWeight = 0.35663;

    double bumpinessWeight = 0.184483;

    std::queue<char> movesQueue;


public:
    std::queue<char> bestMovesQueue;

    AI(double _heightWeight, double _linesWeight, double _holesWeight, double _bumpinessWeight) : heightWeight(_heightWeight),
        linesWeight(_linesWeight), holesWeight(_holesWeight), bumpinessWeight(_bumpinessWeight) {};

    AI() {};

    void findBestPath(GameObjects* piece, Board& board);

    void clear(std::queue<char>& q)
    {
        std::queue<char> empty;
        std::swap(q, empty);
    }

    int moveAndCalcScore(GameObjects const* piece, Board& board,
        int leftSteps, int rightSteps, int roatateSteps);

    int resetAfterDummyMovements(Board& realBoard, Board& snapshotOfOriginalBoard);
};