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
    
    void initLevelMap()
    {
        AI::levelMap[1] = 0;
        AI::levelMap[2] = 40;
        AI::levelMap[3] = 10;
    }

    std::queue<char> movesQueue;
    
    static std::map<int,int> levelMap;
    
    int level = 1; // BEST = 1, GOOD = 2, NOVICE = 3


public:
    std::queue<char> bestMovesQueue;

    AI(double _heightWeight, double _linesWeight, double _holesWeight, double _bumpinessWeight) : heightWeight(_heightWeight),
    linesWeight(_linesWeight), holesWeight(_holesWeight), bumpinessWeight(_bumpinessWeight) {initLevelMap();};

    AI() {initLevelMap();};

    void findBestPath(GameObjects* piece, Board& board);
    
    void AI::generateRandomPath(GameObjects const* piece, Board& board,
                                int leftSteps, int rightSteps, int roatateSteps);
    
    void setLevel(int level);

    void clear(std::queue<char>& q)
    {
        std::queue<char> empty;
        std::swap(q, empty);
    }

    int moveAndCalcScore(GameObjects const* piece, Board& board,
        int leftSteps, int rightSteps, int roatateSteps);

    int resetAfterDummyMovements(Board& realBoard, Board& snapshotOfOriginalBoard);
};
