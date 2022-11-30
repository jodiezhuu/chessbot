#ifndef __PIECE_H__
#define __PIECE_H__
#include "piececolor.h"
#include "../square.h"
#include "piecetype.h"
#include "../board.h"

class Piece {
protected:
    PieceColor color;
    Square *pos;
    PieceType type;
    Board *b;
public:
    Piece(Board *b, PieceColor color, Square *pos, PieceType type);
    PieceType getPieceType();
    PieceColor getColor();
    Square *getPosition();
    virtual bool isMoveValid(int row, int col) = 0;
    virtual Square ** validMoves() = 0;
    virtual Square ** capturingMoves() = 0; 
    virtual bool canBeCaptured() = 0; 
    ~Piece() {};  
};

#endif