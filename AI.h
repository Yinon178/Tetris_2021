#pragma once
#include "board.h"
#include "GameObjects.h"
#include <queue>

class AI
{
    double heightWeight = -0.510066;

    double linesWeight = 0.760666;

    double holesWeight = -0.35663;

    double bumpinessWeight = -0.184483;

    std::queue<char> movesQueue;


public:
    std::queue<char> bestMovesQueue;

    AI(double _heightWeight, double _linesWeight, double _holesWeight, double _bumpinessWeight) : heightWeight(_heightWeight),
        linesWeight(_linesWeight), holesWeight(_holesWeight), bumpinessWeight(_bumpinessWeight) {};

    AI() {};

    void findBestPath(GameObjects* piece, Board const& board)
    {
        std::queue<char> movesQueue;
        auto bestScore = 0;

        for (int rotation = 0; rotation < 4; rotation++) {
            for (int leftMoves = 0; leftMoves < COLS / 2; leftMoves++) {
                for (int rightMoves = 0; rightMoves < COLS / 2; rightMoves++) {
                    double score = 0;
                    score = moveAndCalcScore(piece, board, leftMoves, rightMoves, rotation);
                    if (score > bestScore || bestScore == 0) {
                        bestScore = score;
                        std::swap(bestMovesQueue, movesQueue);
                    }

                }
            }
        }

    }

    void clear(std::queue<char>& q)
    {
        std::queue<char> empty;
        std::swap(q, empty);
    }

    int moveAndCalcScore(GameObjects const *piece, Board const& board,
        int leftSteps, int rightSteps, int roatateSteps)
    {
        Board _board(board);
        GameObjects* _piece = piece->clone();
        _piece->setBoard(_board);
        clear(movesQueue);
        int score = 0;
        for (int step = 0; step < roatateSteps; step++)
        {
            if (!_piece->move(eKEYS::ROUTE))
                return score;
            movesQueue.push(eKEYS::ROUTE);

        }
        for (int step = 0; step < rightSteps; step++)
        {
            if (!_piece->move(eKEYS::LEFT))
                return score;
            movesQueue.push(eKEYS::LEFT);

        }
        for (int step = 0; step < leftSteps; step++)
        {
            if (!_piece->move(eKEYS::RIGHT))
                return score;
            movesQueue.push(eKEYS::RIGHT);

        }

        score = -heightWeight * _board.aggregateHeight() + linesWeight * _board.lines() - holesWeight * _board.holes() - bumpinessWeight * _board.bumpiness();

        delete _piece;
        return score;
    }
};
