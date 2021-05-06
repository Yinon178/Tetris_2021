#pragma once
#include "board.h"
#include "GameObjects.h"
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

    void findBestPath(GameObjects* piece, Board &board)
    {
        double bestScore = -200;
        double score = 0;

        for (int rotation = 0; rotation < 4; rotation++)
        {
            for (int leftMoves = 0; leftMoves < COLS / 2; leftMoves++) {
                score = moveAndCalcScore(piece, board, leftMoves, 0, rotation);
                if (score > bestScore) {
                    bestScore = score;
                    std::swap(bestMovesQueue, movesQueue);
                }
            }
                for (int rightMoves = 0; rightMoves <= COLS / 2; rightMoves++)
                {    
                    score = moveAndCalcScore(piece, board, 0, rightMoves, rotation);
                    if (score > bestScore) {
                        bestScore = score;
                        std::swap(bestMovesQueue, movesQueue);
                    }

                }
        }
    }

    void clear(std::queue<char> &q)
    {
        std::queue<char> empty;
        std::swap(q, empty);
    }

    int moveAndCalcScore(GameObjects const *piece, Board &board,
        int leftSteps, int rightSteps, int roatateSteps)
    {
        Board _board = board;
        GameObjects* _piece = piece->clone();
        bool mark = false;
        clear(movesQueue);
        int score = -10000;
        if (!_piece->move(eKEYS::DEFAULT, mark)) // workaround for some of the shapes that can't rotate in the start
            return score;
        movesQueue.push(eKEYS::DEFAULT);
        for (int step = 0; step < roatateSteps; step++)
        {
            if (!_piece->move(eKEYS::ROUTE, mark))
                return score;
            movesQueue.push(eKEYS::ROUTE);

        }
        for (int step = 0; step < rightSteps; step++)
        {
            if (!_piece->move(eKEYS::RIGHT, mark))
                return score;
            movesQueue.push(eKEYS::RIGHT);

        }
        for (int step = 0; step < leftSteps; step++)
        {
            if (!_piece->move(eKEYS::LEFT, mark))
                return score;
            movesQueue.push(eKEYS::LEFT);

        }
        _piece->move(eKEYS::HARD_DOWN, mark);
        movesQueue.push(eKEYS::HARD_DOWN);
        score = -heightWeight * board.aggregateHeight() + linesWeight * board.lines() - holesWeight * board.holes() - bumpinessWeight * board.bumpiness();
        board = _board; // setting the board back
        
        delete _piece;
        return score;
    }
};
