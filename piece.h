#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "square.h"
#include "piecetype.h"
#include "board.h"
class Piece {
    PieceColor color;
    Square *pos;
    PieceType type;

public:
    PieceType getPieceType();
    PieceColor getColor();
    Square *getPosition();
    virtual bool isMoveValid(int row, int col, PieceColor color, Board *b) = 0;
    virtual Square[] checkMoves(Board *b) = 0;
    virtual Square[] capturingMoves(Board *b) = 0; 
    virtual bool canBeCaptured(Board *b) = 0; 
    ~Piece();  
};

#endif