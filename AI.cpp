#include "AI.h"
#include "Shape.h"
#include "TopBoard.h"


void AI::findBestPath(GameObjects* piece, Board& board)
{
    double bestScore = -200;
    double score = 0;
    clear(bestMovesQueue);
    if (rand() % levelMap[level] == 1 && level != 1) // once every some moves random path will be generated insted of smart move
    {
        int left = rand() % 1;
        int horizontal = rand() % (COLS /2)
        if (left)
            generateRandomPath(piece, board, 0, horizontal, rand() % 4)
        else
            generateRandomPath(piece, board, horizontal, 0, rand() % 4);
        return;
    }

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

void AI::setLevel(int _level)
{
    level = _level;
}

void AI::generateRandomPath(GameObjects const* piece, Board& board,
                            int leftSteps, int rightSteps, int roatateSteps)
{
    Board _board = board;
    std::unique_ptr<GameObjects> _piece{ piece->clone() }; // using uniqe ptr to handle all the return oprations without memory leak
    board.enableDummyTopBoard();
    bool mark = false;
    clear(bestMovesQueue);
    if (_piece->move(eKEYS::DEFAULT, mark)) // workaround for some of the shapes that can't rotate in the start
        movesQueue.push(eKEYS::DEFAULT);
    for (int step = 0; step < roatateSteps; step++)
    {
        if (_piece->move(eKEYS::ROUTE, mark))
            bestMovesQueue.push(eKEYS::ROUTE);

    }
    for (int step = 0; step < rightSteps; step++)
    {
        if (_piece->move(eKEYS::RIGHT, mark))
            bestMovesQueue.push(eKEYS::RIGHT);

    }
    for (int step = 0; step < leftSteps; step++)
    {
        if (_piece->move(eKEYS::LEFT, mark))
            bestMovesQueue.push(eKEYS::LEFT);

    }
    _piece->move(eKEYS::HARD_DOWN, mark);
    bestMovesQueue.push(eKEYS::HARD_DOWN);
    resetAfterDummyMovements(board, _board);
}

int AI::moveAndCalcScore(GameObjects const* piece, Board& board,
    int leftSteps, int rightSteps, int roatateSteps)
{
    Board _board = board;
    std::unique_ptr<GameObjects> _piece{ piece->clone() }; // using uniqe ptr to handle all the return oprations without memory leak
    board.enableDummyTopBoard();
    bool mark = false;
    clear(movesQueue);
    int score = -10000;

    if (!_piece->move(eKEYS::DEFAULT, mark)) // workaround for some of the shapes that can't rotate in the start
        return resetAfterDummyMovements(board, _board);
    movesQueue.push(eKEYS::DEFAULT);
    for (int step = 0; step < roatateSteps; step++)
    {
        if (!_piece->move(eKEYS::ROUTE, mark))
            return resetAfterDummyMovements(board, _board);
        movesQueue.push(eKEYS::ROUTE);

    }
    for (int step = 0; step < rightSteps; step++)
    {
        if (!_piece->move(eKEYS::RIGHT, mark))
            return resetAfterDummyMovements(board, _board);
        movesQueue.push(eKEYS::RIGHT);

    }
    for (int step = 0; step < leftSteps; step++)
    {
        if (!_piece->move(eKEYS::LEFT, mark))
            return resetAfterDummyMovements(board, _board);
        movesQueue.push(eKEYS::LEFT);

    }
    _piece->move(eKEYS::HARD_DOWN, mark);
    movesQueue.push(eKEYS::HARD_DOWN);
    score = -heightWeight * board.aggregateHeight() + linesWeight * board.lines() - holesWeight * board.holes() - bumpinessWeight * board.bumpiness();
    resetAfterDummyMovements(board, _board);
    return score;
}

int AI::resetAfterDummyMovements(Board &realBoard, Board &snapshotOfOriginalBoard)
{
    int scoreAfterFailedMove = -11000;
    realBoard.disablesDummyTopBoard();
    realBoard = snapshotOfOriginalBoard; // setting the board back
    return scoreAfterFailedMove;
}

