#pragma once
#include "GameObjects.h"
#include "board.h"
#include "GameObjects.h"
#include <queue>

class AI
{
	double heightWeight = -0.510066;
   
	double linesWeight = 0.760666;
   
	double holesWeight = -0.35663;
   
	double bumpinessWeight = -0.184483;
    
    std::queue<char> bestMovesQueue;
    
    
    
    auto _best(Board board, Shape shape);


public:
    
	AI(double _heightWeight, double _linesWeight, double _holesWeight, double _bumpinessWeight) : heightWeight(_heightWeight),
		linesWeight(_linesWeight), holesWeight(_holesWeight), bumpinessWeight(_bumpinessWeight) {};
    
    AI();

//    auto best(Board board, Shape shape);
    
    findBestPath(GameObjects *piece, Board const &board)
    {
        std::queue<char> movesQueue;
        auto bestScore = 0;
        clear(movesQueue);
        for(int rotation = 0; rotation < 4; rotation++){
            Board _board(board);
            GameObjects *_piece = piece.clone();
            for(int i = 0; i < rotation; i++)
            {
                if(!_piece->move(eKEYS::ROUTE))
                    continue;
                movesQueue.push(eKEYS::ROUTE)
            }

               while(_piece.move(eKEYS::LEFT))
                   movesQueue.push(eKEYS::LEFT);

               while(board.valid(_piece)){
                   GameObjects * _pieceSet = _piece.clone();
                   while(_pieceSet.moveDown(board));

                   Board _board(board);
                   _board.addPiece(_pieceSet);

                   double score = 0;
                   score = -heightWeight * _board.aggregateHeight() + linesWeight * _board.lines() - holesWeight * _board.holes() - bumpinessWeight * _board.bumpiness();

                   if (score > bestScore || bestScore == 0){
                       bestScore = score;
                       std::swap(bestMovesQueue, movesQueue);
                   }

                   _piece.column++;
               }
            delete _piece;
           }
        
        
    }
    
    void clear( std::queue<char> &q )
    {
       std::queue<char> empty;
       std::swap( q, empty );
    }
};

